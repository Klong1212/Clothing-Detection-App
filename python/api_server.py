# api_server.py
from fastapi import FastAPI, UploadFile, File
from fastapi.responses import Response
import cv2
import numpy as np
import io
from PIL import Image

# Import คลาสจากไฟล์ของคุณ
from fashion_segmenter import SimpleFashionSegmenter

app = FastAPI()

# โหลดโมเดลรอไว้เลย (ทำแค่ครั้งเดียวตอนเริ่มรัน Server)
print("⏳ Initializing Models... Please wait.")
segmenter = SimpleFashionSegmenter()
print("✅ Server is ready!")

@app.post("/segment")
async def segment_image(file: UploadFile = File(...)):
    # 1. รับไฟล์รูปภาพจาก C#
    contents = await file.read()
    nparr = np.frombuffer(contents, np.uint8)
    image_np = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
    
    # เนื่องจาก cv2 อ่านเป็น BGR แต่ model ต้องการ RGB หรือ path
    # เราต้องปรับแก้ method segment ใน class นิดหน่อย หรือ save เป็น temp file
    # แต่วิธีที่ง่ายที่สุดคือ save เป็น temp file เพื่อให้เข้ากับโค้ดเดิมของคุณ
    temp_filename = "temp_upload.jpg"
    cv2.imwrite(temp_filename, image_np)
    
    # 2. เรียกใช้ฟังก์ชัน segment ของคุณ
    # หมายเหตุ: โค้ดเดิมของคุณรับ image_path
    original_image, seg_map, detected_items = segmenter.segment(temp_filename)
    
    # 3. สร้างรูปผลลัพธ์ (แบบมี Label)
    result_image = segmenter.visualize_with_labels(original_image, detected_items, alpha=0.5)
    
    # 4. แปลงรูปผลลัพธ์กลับเป็น bytes เพื่อส่งคืน C#
    # แปลง RGB (Matplotlib/PIL) กลับเป็น BGR (OpenCV) ก่อนส่งถ้ายริบรารี่ visualize คืนค่ามาเป็น RGB
    # แต่ถ้า visualize คืนค่ามาเป็น RGB อยู่แล้ว และต้องการส่งกลับเป็น JPEG ต้องแปลงสีให้ถูก
    # สมมติว่า visualize คืนค่าเป็น RGB
    result_bgr = cv2.cvtColor(result_image, cv2.COLOR_RGB2BGR)
    _, encoded_img = cv2.imencode('.jpg', result_bgr)
    
    return Response(content=encoded_img.tobytes(), media_type="image/jpeg")

if __name__ == "__main__":
    import uvicorn
    # รัน Server ที่ localhost พอร์ต 8000
    uvicorn.run(app, host="127.0.0.1", port=8000)