import cv2
import numpy as np
import torch
import matplotlib.pyplot as plt
from transformers import AutoImageProcessor, AutoModelForSemanticSegmentation, pipeline
from PIL import Image
from ultralytics import YOLO

class SimpleFashionSegmenter:
    """
    โปรแกรมแบ่งส่วนเสื้อผ้าอย่างละเอียด
    ใช้โมเดล Human Parsing ที่เทรนมาเฉพาะสำหรับแยกเสื้อผ้า
    """
    
    def __init__(self):
        self.device = "cuda" if torch.cuda.is_available() else "cpu"
        print(f"🚀 Loading Human Parsing Model on {self.device}...")
        
        # ใช้โมเดล Human Parsing ที่แยกรายละเอียดเสื้อผ้าได้ละเอียด
        model_name = "mattmdjaga/segformer_b2_clothes"
        
        self.processor = AutoImageProcessor.from_pretrained(model_name)
        self.model = AutoModelForSemanticSegmentation.from_pretrained(model_name)
        self.model.to(self.device)
        self.model.eval()
        
        # โหลด YOLOv8 สำหรับตรวจจับ accessories เพิ่มเติม
        print("  - Loading YOLOv8 for accessories detection...")
        self.yolo = YOLO('yolov8m.pt')
        
        # เพิ่ม CLIP สำหรับจำแนกชนิดเสื้อผ้า
        print("  - Loading CLIP Classifier...")
        self.classifier = pipeline(
            "zero-shot-image-classification",
            model="openai/clip-vit-base-patch32",
            device=0 if self.device == "cuda" else -1
        )
        
        # Label mapping สำหรับโมเดล Human Parsing
        # เก็บเฉพาะเสื้อผ้าและอุปกรณ์เสริม ไม่รวมอวัยวะ
        self.label_names = [
            'Background',      # 0
            'Hat',            # 1 - หมวก
            'Hair',           # 2 - ผม (ออก)
            'Sunglasses',     # 3 - แว่นกันแดด
            'Upper-clothes',  # 4 - เสื้อ
            'Skirt',          # 5 - กระโปรง
            'Pants',          # 6 - กางเกง
            'Dress',          # 7 - ชุดเดรส
            'Belt',           # 8 - เข็มขัด
            'Left-shoe',      # 9 - รองเท้าซ้าย
            'Right-shoe',     # 10 - รองเท้าขวา
            'Face',           # 11 - ใบหน้า (ออก)
            'Left-leg',       # 12 - ขาซ้าย (ออก)
            'Right-leg',      # 13 - ขาขวา (ออก)
            'Left-arm',       # 14 - แขนซ้าย (ออก)
            'Right-arm',      # 15 - แขนขวา (ออก)
            'Bag',            # 16 - กระเป๋า
            'Scarf',          # 17 - ผ้าพันคอ
        ]
        
        # เก็บเฉพาะสิ่งที่เป็นเสื้อผ้า ไม่มีอวัยวะ
        self.clothing_labels = {
            1, 3, 4, 5, 6, 7, 8, 9, 10, 16, 17  # Hat, Sunglasses, Upper, Skirt, Pants, Dress, Belt, Shoes, Bag, Scarf
        }
        
        # YOLO class IDs ที่เกี่ยวข้องกับแฟชั่น (ไม่รวม Person)
        self.yolo_fashion_classes = {
            24: 'Handbag',
            26: 'Backpack', 
            27: 'Umbrella',
            28: 'Tie',        # เน็กไท
            31: 'Suitcase',
        }
        
        # กำหนดสีสำหรับแต่ละส่วน (เฉพาะเสื้อผ้า)
        self.color_map = {
            'Hat': (255, 200, 120),         # ส้มอ่อน
            'Sunglasses': (100, 100, 100),  # เทา
            'Upper-clothes': (150, 255, 180),  # เขียวมิ้นท์
            'Skirt': (255, 150, 200),       # ชมพูเข้ม
            'Pants': (180, 200, 255),       # ฟ้าอ่อน
            'Dress': (255, 200, 255),       # ม่วงอ่อน
            'Belt': (101, 67, 33),          # น้ำตาลเข้ม
            'Left-shoe': (200, 180, 255),   # ม่วงฟ้า
            'Right-shoe': (200, 180, 255),  # ม่วงฟ้า
            'Bag': (255, 180, 120),         # ส้มครีม
            'Scarf': (220, 160, 255),       # ม่วงพาสเทล
            'Tie': (50, 100, 180),          # น้ำเงินเข้ม
            'Watch': (192, 192, 192),       # เงิน
            'Necklace': (255, 215, 0),      # ทอง
            'Earrings': (255, 182, 193),    # ชมพูอ่อน
            'Bracelet': (255, 215, 0),      # ทอง
            'Ring': (192, 192, 192),        # เงิน
            'Handbag': (255, 150, 120),
            'Backpack': (150, 200, 150),
            'Umbrella': (200, 200, 100),
            'Suitcase': (200, 150, 100),
        }
        
        print("✅ Model Ready!\n")
    
    def get_clothing_candidates(self, category):
        """
        คำศัพท์สำหรับ CLIP จำแนกแต่ละประเภท - เพิ่มให้เยอะขึ้นเพื่อการจำแนกที่ละเอียดขึ้น
        """
        candidates = {
            'Hat': ["Baseball Cap", "Beanie", "Beret", "Fedora", "Sun Hat", "Winter Hat", "Panama Hat", "Bucket Hat", "Snapback Cap", "Trucker Hat", "Visor", "Top Hat", "Bowler Hat", "Newsboy Cap", "Cowboy Hat", "Straw Hat"],
            'Upper-clothes': ["Blazer", "Suit Jacket", "T-shirt", "Blouse", "Shirt", "Sweater", "Hoodie", "Tank Top", "Vest", "Cardigan", "Polo Shirt", "Henley Shirt", "Crop Top", "Tube Top", "Off-shoulder Top", "Sweatshirt", "Denim Jacket", "Leather Jacket", "Bolero Jacket", "Sports Coat", "Windbreaker", "Puffer Jacket", "Wool Coat", "Trench Coat", "Peacoat", "Long Sleeve Shirt", "Short Sleeve Shirt", "Button-up Shirt", "Oversized Shirt", "Fitted Shirt"],
            'Skirt': ["Mini Skirt", "Midi Skirt", "Maxi Skirt", "Pleated Skirt", "Pencil Skirt", "A-Line Skirt", "Denim Skirt", "Flared Skirt", "Wrap Skirt", "Asymmetrical Skirt", "Tennis Skirt", "Tulle Skirt", "Slit Skirt"],
            'Pants': ["Jeans", "Slacks", "Cargo Pants", "Wide-leg Trousers", "Leggings", "Chinos", "Dress Pants", "Joggers", "Capri Pants", "Shorts", "Bermuda Shorts", "Hot Pants", "Bike Shorts", "Skinny Jeans", "Bootcut Jeans", "Flared Jeans", "Straight Leg Jeans", "Distressed Jeans", "High-waisted Pants", "Low-rise Pants", "Culottes", "Palazzo Pants"],
            'Dress': ["Cocktail Dress", "Maxi Dress", "Mini Dress", "Shirt Dress", "Wrap Dress", "A-Line Dress", "Evening Gown", "Sundress", "Bodycon Dress", "Flowy Dress", "Shift Dress", "Fit and Flare Dress", "Halter Dress", "Strapless Dress", "One-shoulder Dress", "Backless Dress", "Sheath Dress", "Jumper Dress", "Slip Dress", "Tea Dress"],
            'Left-shoe': ["Sneakers", "High Heels", "Boots", "Sandals", "Flats", "Leather Shoes", "Loafers", "Oxfords", "Ankle Boots", "Knee-high Boots", "Combat Boots", "Chelsea Boots", "Pumps", "Wedges", "Platforms", "Ballet Flats", "Moccasins", "Slip-ons", "Slippers", "Tennis Shoes", "Running Shoes", "Hiking Boots", "Dress Shoes", "Casual Shoes"],
            'Right-shoe': ["Sneakers", "High Heels", "Boots", "Sandals", "Flats", "Leather Shoes", "Loafers", "Oxfords", "Ankle Boots", "Knee-high Boots", "Combat Boots", "Chelsea Boots", "Pumps", "Wedges", "Platforms", "Ballet Flats", "Moccasins", "Slip-ons", "Slippers", "Tennis Shoes", "Running Shoes", "Hiking Boots", "Dress Shoes", "Casual Shoes"],
            'Bag': ["Handbag", "Backpack", "Tote Bag", "Clutch", "Crossbody Bag", "Shoulder Bag", "Messenger Bag", "Satchel", "Hobo Bag", "Bucket Bag", "Drawstring Bag", "Clutch Purse", "Evening Bag", "Weekender Bag", "Travel Bag", "Gym Bag", "Duffel Bag", "Shoulder Purse", "Chain Bag", "Structured Handbag"],
            'Scarf': ["Silk Scarf", "Wool Scarf", "Neck Scarf", "Head Scarf", "Infinity Scarf", "Pashmina", "Cashmere Scarf", "Shawl", "Wrap", "Stole", "Bandana", "Neckerchief"],
            'Sunglasses': ["Aviator Sunglasses", "Wayfarer Sunglasses", "Round Sunglasses", "Cat-eye Sunglasses", "Oversized Sunglasses", "Clubmaster Sunglasses", "Shield Sunglasses", "Gradient Sunglasses", "Mirrored Sunglasses", "Polarized Sunglasses", "Sporty Sunglasses"],
            'Tie': ["Necktie", "Bow Tie", "Slim Tie", "Knit Tie", "Silk Tie", "Wide Tie", "Skinny Tie", "Clip-on Tie"],
            'Watch': ["Wristwatch", "Smart Watch", "Analog Watch", "Digital Watch", "Dress Watch", "Sports Watch", "Luxury Watch", "Casual Watch"],
            'Belt': ["Leather Belt", "Fabric Belt", "Chain Belt", "Wide Belt", "Skinny Belt", "Woven Belt", "Braided Belt", "Western Belt"],
            'Sunglasses': ["Aviator", "Wayfarer", "Round Frame", "Cat-eye", "Oversized", "Clubmaster", "Shield", "Gradient Lens"],
            'Necklace': ["Chain Necklace", "Pendant Necklace", "Choker", "Pearl Necklace", "Statement Necklace", "Lariat Necklace", "Y Necklace", "Layered Necklace"],
            'Earrings': ["Stud Earrings", "Hoop Earrings", "Drop Earrings", "Chandelier Earrings", "Pearl Earrings", "Tassel Earrings"],
            'Bracelet': ["Bangle", "Charm Bracelet", "Chain Bracelet", "Cuff Bracelet", "Tennis Bracelet", "Beaded Bracelet"],
            'Ring': ["Wedding Ring", "Cocktail Ring", "Signet Ring", "Band Ring", "Statement Ring", "Promise Ring"],
        }
        return candidates.get(category, None)
    
    def classify_clothing(self, image, mask, category):
        """
        ใช้ CLIP จำแนกชนิดเสื้อผ้า
        """
        candidates = self.get_clothing_candidates(category)
        
        # ถ้าไม่มี candidates หรือไม่ต้องการจำแนก ให้ return ชื่อเดิม
        if candidates is None:
            return category
        
        try:
            # ตัดส่วนที่ต้องการออกมา (crop region)
            masked_region = image.copy()
            masked_region[~mask] = 255  # พื้นหลังขาว
            
            # แปลงเป็น PIL Image
            pil_image = Image.fromarray(masked_region)
            
            # จำแนกด้วย CLIP
            results = self.classifier(pil_image, candidate_labels=candidates)
            
            # ถ้า confidence สูงกว่า 25% ให้ใช้ชื่อที่ละเอียดกว่า
            if results and results[0]['score'] > 0.25:
                return results[0]['label']
            else:
                return category
                
        except Exception as e:
            print(f"    ⚠ CLIP classification failed: {e}")
            return category
    
    def detect_accessories_with_yolo(self, image_np):
        """
        ใช้ YOLOv8 ตรวจจับ accessories เพิ่มเติม เช่น เน็กไท กระเป๋า
        """
        print("🔍 Detecting accessories with YOLO...")
        results = self.yolo(image_np, verbose=False)
        
        accessories = []
        
        for result in results:
            boxes = result.boxes
            for box in boxes:
                cls = int(box.cls[0])
                conf = float(box.conf[0])
                
                # ใช้ threshold ต่ำกว่าสำหรับเน็กไท (class 28) เพราะมันเล็กและยากตรวจจับ
                min_conf = 0.15 if cls == 28 else 0.4
                
                # เช็คว่าเป็น class ที่เกี่ยวกับแฟชั่นหรือไม่
                if cls in self.yolo_fashion_classes and conf > min_conf:
                    x1, y1, x2, y2 = map(int, box.xyxy[0])
                    
                    # สร้าง mask จาก bounding box
                    mask = np.zeros(image_np.shape[:2], dtype=bool)
                    mask[y1:y2, x1:x2] = True
                    
                    label = self.yolo_fashion_classes[cls]
                    
                    # ข้าม Person
                    if label == 'Person':
                        continue
                    
                    # แปลงชื่อให้เหมาะสม
                    if label == 'Handbag':
                        label = 'Bag'
                    
                    area = (x2 - x1) * (y2 - y1)
                    
                    print(f"  🎯 Found: {label.upper()} (confidence: {conf:.2f})")
                    
                    # ใช้ CLIP ลองจำแนกเพิ่ม
                    detailed_label = self.classify_clothing(image_np, mask, label)
                    
                    accessories.append({
                        'label': detailed_label,
                        'mask': mask,
                        'area': area,
                        'color': self.color_map.get(label, (150, 150, 150)),
                        'bbox': (x1, y1, x2, y2),
                        'confidence': conf
                    })
                    print(f"     ✅ Classified as: {detailed_label.upper()}")
        
        return accessories
    
    def detect_tie_region(self, image_np, detected_items):
        """
        ตรวจจับเน็กไทด์จากตำแหน่งระหว่างใบหน้าและเสื้อ
        """
        print("  🔎 Analyzing neck region for tie...")
        
        # หา Face และ Upper-clothes
        face_item = None
        upper_item = None
        
        for item in detected_items:
            label = item['label']
            if 'Face' in label or label == 'Face':
                face_item = item
                print(f"    ✓ Found face")
            elif any(x in label for x in ['Upper-clothes', 'Blazer', 'Suit Jacket', 'Shirt', 'T-shirt', 'Blouse']):
                upper_item = item
                print(f"    ✓ Found upper clothing: {label}")
        
        if face_item is None:
            print("    ✗ No face detected")
            return None
        if upper_item is None:
            print("    ✗ No upper clothing detected")
            return None
        
        # หาตำแหน่งใบหน้า
        face_ys, face_xs = np.where(face_item['mask'])
        if len(face_ys) == 0:
            print("    ✗ Face mask is empty")
            return None
        
        face_bottom = face_ys.max()
        face_center_x = int(face_xs.mean())
        print(f"    📍 Face bottom at y={face_bottom}, center x={face_center_x}")
        
        # หาตำแหน่งเสื้อ
        upper_ys, upper_xs = np.where(upper_item['mask'])
        if len(upper_ys) == 0:
            print("    ✗ Upper clothing mask is empty")
            return None
        
        upper_top = upper_ys.min()
        print(f"    📍 Upper clothing top at y={upper_top}")
        
        # ตำแหน่งเน็กไทด์น่าจะอยู่ระหว่างใบหน้ากับเสื้อ
        if face_bottom >= upper_top:
            print(f"    ✗ No space for tie (face_bottom={face_bottom} >= upper_top={upper_top})")
            return None
        
        # สร้าง region สำหรับตรวจสอบเน็กไท
        neck_height = upper_top - face_bottom
        print(f"    📏 Neck height: {neck_height} pixels")
        
        if neck_height < 10:  # ลดเงื่อนไขจาก 20
            print(f"    ✗ Neck region too small ({neck_height} < 10 pixels)")
            return None
        
        # กำหนด bounding box สำหรับ neck region
        tie_width = int(image_np.shape[1] * 0.08)  # ประมาณ 8% ของความกว้างภาพ
        tie_x1 = max(0, face_center_x - tie_width // 2)
        tie_x2 = min(image_np.shape[1], face_center_x + tie_width // 2)
        tie_y1 = face_bottom
        tie_y2 = min(image_np.shape[0], face_bottom + int(neck_height * 2.5))
        
        # ตัดส่วน neck region
        neck_region = image_np[tie_y1:tie_y2, tie_x1:tie_x2]
        
        if neck_region.size == 0:
            return None
        
        # ใช้ CLIP ตรวจสอบว่ามีเน็กไทด์หรือไม่
        try:
            pil_image = Image.fromarray(neck_region)
            candidates = ["necktie", "bow tie", "striped tie", "solid tie", "no tie", "bare neck"]
            results = self.classifier(pil_image, candidate_labels=candidates)
            
            print(f"    🔬 CLIP results for neck region: {results[0]['label']} ({results[0]['score']:.2f})")
            
            # ถ้า confidence ของ tie มากกว่า 20% ถือว่ามีเน็กไท
            if results and results[0]['score'] > 0.20 and 'tie' in results[0]['label'].lower():
                print(f"  🎯 Found TIE in neck region (CLIP confidence: {results[0]['score']:.2f})")
                
                # สร้าง mask สำหรับเน็กไท
                mask = np.zeros(image_np.shape[:2], dtype=bool)
                mask[tie_y1:tie_y2, tie_x1:tie_x2] = True
                
                detailed_label = self.classify_clothing(image_np, mask, 'Tie')
                
                return {
                    'label': detailed_label,
                    'mask': mask,
                    'area': (tie_x2 - tie_x1) * (tie_y2 - tie_y1),
                    'color': self.color_map.get('Tie', (50, 100, 180)),
                    'bbox': (tie_x1, tie_y1, tie_x2, tie_y2),
                    'confidence': results[0]['score']
                }
        except Exception as e:
            print(f"    ⚠ Tie detection failed: {e}")
        
        return None
    
    def segment(self, image_path):
        """
        แบ่งส่วนเสื้อผ้าในภาพ
        
        Args:
            image_path: ไฟล์รูปภาพ
            
        Returns:
            original_image, segmentation_map, detected_labels
        """
        print(f"📸 Processing: {image_path}")
        
        # 1. โหลดรูป
        image = Image.open(image_path).convert('RGB')
        image_np = np.array(image)
        
        # 2. เตรียมข้อมูลสำหรับโมเดล
        inputs = self.processor(images=image, return_tensors="pt")
        inputs = {k: v.to(self.device) for k, v in inputs.items()}
        
        # 3. ทำนายผล
        print("🔍 Detecting clothing items...")
        with torch.no_grad():
            outputs = self.model(**inputs)
            logits = outputs.logits
        
        # 4. แปลง output เป็น segmentation map
        # Resize กลับเป็นขนาดเดิม
        seg_map = torch.nn.functional.interpolate(
            logits,
            size=image_np.shape[:2],
            mode='bilinear',
            align_corners=False
        )
        seg_map = seg_map.argmax(dim=1)[0].cpu().numpy()
        
        # 5. หา labels ที่ตรวจพบ
        unique_labels = np.unique(seg_map)
        detected_items = []
        
        for label_id in unique_labels:
            # ข้าม Background (0) และอวัยวะ
            if label_id == 0:
                continue
            
            # ข้ามอวัยวะ (Face, Left-leg, Right-leg, Left-arm, Right-arm, Hair)
            if label_id not in self.clothing_labels:
                continue
                
            # ตรวจสอบว่า label_id อยู่ในช่วงที่ถูกต้อง
            if label_id < len(self.label_names):
                label_name = self.label_names[label_id]
                mask = (seg_map == label_id)
                area = np.sum(mask)
                
                # กรองสิ่งที่เล็กเกินไป (Noise)
                if area > 500:  # อย่างน้อย 500 pixels
                    print(f"  🔍 Found: {label_name.upper()} ({area} pixels)")
                    
                    # ใช้ CLIP จำแนกชนิดเสื้อผ้าที่ละเอียดขึ้น
                    detailed_label = self.classify_clothing(image_np, mask, label_name)
                    
                    detected_items.append({
                        'label': detailed_label,
                        'mask': mask,
                        'area': area,
                        'color': self.color_map.get(label_name, (200, 200, 200))
                    })
                    print(f"     ✅ Classified as: {detailed_label.upper()}")
        
        # 6. ตรวจจับ accessories เพิ่มเติมด้วย YOLO
        yolo_items = self.detect_accessories_with_yolo(image_np)
        
        # รวม YOLO items เข้ากับ detected items (ไม่ซ้ำ)
        for yolo_item in yolo_items:
            # เช็คว่าไม่ซ้ำกับที่มีอยู่แล้ว
            is_duplicate = False
            for existing_item in detected_items:
                # คำนวณ overlap
                intersection = np.logical_and(yolo_item['mask'], existing_item['mask'])
                overlap = np.sum(intersection) / np.sum(yolo_item['mask']) if np.sum(yolo_item['mask']) > 0 else 0
                
                if overlap > 0.5:  # ถ้าซ้อนกันมากกว่า 50%
                    is_duplicate = True
                    break
            
            if not is_duplicate:
                detected_items.append(yolo_item)
        
        # 7. ถ้ายังไม่เจอเน็กไท ลองใช้ heuristic detection
        has_tie = any('Tie' in item['label'] or 'tie' in item['label'].lower() for item in detected_items)
        if not has_tie:
            print("🔍 Trying heuristic tie detection...")
            tie_item = self.detect_tie_region(image_np, detected_items)
            if tie_item:
                detected_items.append(tie_item)
                print(f"     ✅ Classified as: {tie_item['label'].upper()}")
        
        # เรียงตามตำแหน่ง (บนลงล่าง)
        # หาตำแหน่ง Y เฉลี่ยของแต่ละส่วน
        for item in detected_items:
            ys, _ = np.where(item['mask'])
            item['avg_y'] = ys.mean() if len(ys) > 0 else 0
        
        detected_items.sort(key=lambda x: x['avg_y'])
        
        return image_np, seg_map, detected_items
    
    def visualize(self, image, detected_items, alpha=0.5):
        """
        สร้างภาพผลลัพธ์ถมสีแต่ละส่วน
        
        Args:
            image: รูปต้นฉบับ (numpy array)
            detected_items: รายการสิ่งที่ตรวจพบ
            alpha: ความโปร่งใสของสี (0-1)
            
        Returns:
            result_image
        """
        print("\n🎨 Creating visualization...")
        
        # สร้าง overlay สำหรับถมสี
        overlay = image.copy()
        
        for item in detected_items:
            mask = item['mask']
            color = item['color']
            
            # ถมสีในส่วนที่ mask
            overlay[mask] = color
            
            # วาดขอบให้คมชัด
            contours, _ = cv2.findContours(
                mask.astype(np.uint8),
                cv2.RETR_EXTERNAL,
                cv2.CHAIN_APPROX_SIMPLE
            )
            
            # สีขอบเข้มกว่าสีถมนิดหน่อย
            border_color = tuple([max(0, c - 50) for c in color])
            cv2.drawContours(overlay, contours, -1, border_color, 2, cv2.LINE_AA)
        
        # รวมภาพต้นฉบับกับสีที่ถม (Alpha Blending)
        result = cv2.addWeighted(overlay, alpha, image, 1 - alpha, 0)
        
        return result
    
    def visualize_with_labels(self, image, detected_items, alpha=0.5):
        """
        สร้างภาพพร้อมป้ายชื่อแต่ละส่วน
        """
        # เริ่มจากภาพที่ถมสีแล้ว
        result = self.visualize(image, detected_items, alpha)
        
        # เพิ่มป้ายชื่อ
        for item in detected_items:
            mask = item['mask']
            label = item['label']
            color = item['color']
            
            # ถ้ามี bbox (จาก YOLO) ให้ใช้ bbox
            if 'bbox' in item:
                x1, y1, x2, y2 = item['bbox']
                center_x = (x1 + x2) // 2
                center_y = (y1 + y2) // 2
                
                # วาด bounding box
                cv2.rectangle(result, (x1, y1), (x2, y2), color, 2)
            else:
                # หาจุดกึ่งกลางของ mask
                ys, xs = np.where(mask)
                if len(xs) == 0:
                    continue
                center_x = int(xs.mean())
                center_y = int(ys.mean())
            
            # สีข้อความ (เข้มกว่าพื้น)
            text_color = tuple([max(0, c - 80) for c in color])
            
            # วาดพื้นหลังข้อความ
            label_text = label.upper()
            font = cv2.FONT_HERSHEY_SIMPLEX
            font_scale = 0.7
            thickness = 2
            
            (tw, th), _ = cv2.getTextSize(label_text, font, font_scale, thickness)
            
            # พื้นหลังกล่อง
            padding = 6
            bg_pt1 = (center_x - tw//2 - padding, center_y - th - padding)
            bg_pt2 = (center_x + tw//2 + padding, center_y + padding)
            
            # วาดกล่องพื้นหลัง (โปร่งแสง)
            sub_overlay = result.copy()
            cv2.rectangle(sub_overlay, bg_pt1, bg_pt2, color, -1)
            result = cv2.addWeighted(sub_overlay, 0.7, result, 0.3, 0)
            
            # วาดข้อความ
            text_pos = (center_x - tw//2, center_y)
            cv2.putText(result, label_text, text_pos, font, font_scale, 
                       (255, 255, 255), thickness + 1, cv2.LINE_AA)
            cv2.putText(result, label_text, text_pos, font, font_scale, 
                       (0, 0, 0), thickness - 1, cv2.LINE_AA)
            
            # เพิ่มข้อมูล confidence ถ้ามี
            if 'confidence' in item:
                conf_text = f"{item['confidence']:.0%}"
                conf_pos = (center_x - tw//2, center_y + th + 5)
                cv2.putText(result, conf_text, conf_pos, font, 0.5, 
                           (255, 255, 255), 2, cv2.LINE_AA)
                cv2.putText(result, conf_text, conf_pos, font, 0.5, 
                           (0, 0, 0), 1, cv2.LINE_AA)
        
        return result


def main():
    """ตัวอย่างการใช้งาน"""
    
    # ตั้งค่า
    IMAGE_PATH = "114296429.jpg"  # เปลี่ยนเป็นรูปของคุณ
    OUTPUT_SIMPLE = "result_simple.jpg"
    OUTPUT_LABELED = "result_labeled.jpg"
    
    try:
        # 1. สร้าง Segmenter
        segmenter = SimpleFashionSegmenter()
        
        # 2. แบ่งส่วนเสื้อผ้า
        original_image, seg_map, detected_items = segmenter.segment(IMAGE_PATH)
        
        if not detected_items:
            print("\n⚠️  No clothing items detected!")
            return
        
        # 3. สร้างภาพผลลัพธ์แบบเรียบง่าย (แค่ถมสี)
        result_simple = segmenter.visualize(original_image, detected_items, alpha=0.6)
        
        # 4. สร้างภาพผลลัพธ์แบบมีป้ายชื่อ
        result_labeled = segmenter.visualize_with_labels(original_image, detected_items, alpha=0.5)
        
        # 5. บันทึกไฟล์
        cv2.imwrite(OUTPUT_SIMPLE, cv2.cvtColor(result_simple, cv2.COLOR_RGB2BGR))
        cv2.imwrite(OUTPUT_LABELED, cv2.cvtColor(result_labeled, cv2.COLOR_RGB2BGR))
        
        print(f"\n💾 Saved results:")
        print(f"  📁 {OUTPUT_SIMPLE}")
        print(f"  📁 {OUTPUT_LABELED}")
        
        # 6. แสดงผล
        fig, axes = plt.subplots(1, 3, figsize=(18, 6))
        
        axes[0].imshow(original_image)
        axes[0].set_title("Original Image", fontsize=14, fontweight='bold')
        axes[0].axis('off')
        
        axes[1].imshow(result_simple)
        axes[1].set_title("Segmented (Simple)", fontsize=14, fontweight='bold')
        axes[1].axis('off')
        
        axes[2].imshow(result_labeled)
        axes[2].set_title("Segmented (With Labels)", fontsize=14, fontweight='bold')
        axes[2].axis('off')
        
        plt.tight_layout()
        plt.savefig("comparison.jpg", dpi=150, bbox_inches='tight')
        print(f"  📁 comparison.jpg")
        plt.show()
        
        print("\n✨ Done!")
        
    except Exception as e:
        print(f"\n❌ Error: {e}")
        import traceback
        traceback.print_exc()


if __name__ == "__main__":
    main()