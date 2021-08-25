#import
import cv2 as cv
import numpy as np

#python -m pip install opencv-python  #opencv
#pip install matplotlib               #matplot 설치

##############################################################
## MAT 생성 및 값 설정
image1 = np.zeros((150, 100), np.uint8)
image2 = np.ones((150, 100), np.uint8) * 255
image3 = np.full((150, 100), 255, np.uint8)
image4 = np.full((150, 100, 3), (0, 255, 255), np.uint8)

image4_copy = image4.copy()
image4_copy_crop = image4[100:150, 50:100].copy()   #깊은복사
image4_crop = image4[100:150, 50:100]               #앝은복사

image4_crop.fill(0)                                 #0으로 채우기
image4_crop[:] = (255, 0,0)                         #컬러값을 채우기
image4_crop[:, 0:10] = (0, 0,255)                   #컬러값을 채우기

cv.imshow("image4", image4)
cv.imshow("image4_copy", image4_copy)
cv.imshow("image4_copy_crop", image4_copy_crop)
cv.waitKey(0)
cv.destroyAllWindows()

image4_array = np.full(image4.shape, (0, 255, 0), np.uint8)
image4 = cv.add(image4, image4_array)
image4 = cv.subtract(image4, image4_array)
cv.imshow("image4", image4)
cv.waitKey(0)
cv.destroyAllWindows()

#############################################################
# 픽셀 접근
image1 = np.zeros((50, 512), np.uint8)         # 50 x 512 영상
image2 = np.zeros((50, 512), np.uint8)

rows, cols = image1.shape

def pixel_access(image1, image2):
    for i in range(rows):                       
        for j in range(cols):
            image1.itemset((i, j), j + 10)        
            pixel = image2[i,j]                  
            image2[i, j] =  j * 5 - pixel         

pixel_access(image1, image2);

cv.imshow("image1", image1)
cv.imshow("image2", image2)
cv.waitKey(0)
cv.destroyAllWindows()

##############################################################
# 영상 로드 및 영상 블렌딩
load1 = cv.imread("./flower.jpg", cv.IMREAD_COLOR);
load2 = cv.imread("./head.jpg", cv.IMREAD_COLOR);

print(load1.shape)
print(load2.shape)

size = load1.shape[-2::-1]
print(size)
resize_load2 = cv.resize(load2, size, 0, 0, cv.INTER_CUBIC)

print(load1.shape, resize_load2.shape)
blend = cv.addWeighted(load1, 0.7, resize_load2, 0.3, 0)
cv.imshow("blend", blend)
cv.waitKey(0)
cv.destroyAllWindows()


##############################################################
## 히스토그램 opencv이용 표시
def draw_histo(hist, shape=(200, 256)):
    hist_img = np.full( shape, 255, np.uint8)
    cv.normalize(hist, hist, 0, shape[0], cv.NORM_MINMAX)
    gap = hist_img.shape[1]/hist.shape[0]               

    for i, h in enumerate(hist):
        x = int(round(i * gap))                         # 막대 사각형 시작 x 좌표
        w = int(round(gap))
        roi = (x, 0, w, int(h))
        cv.rectangle(hist_img, roi, 0, cv.FILLED)

    return cv.flip(hist_img, 0)                        # 상하 뒤집은 후 return

image = cv.imread("./flower.jpg", cv.IMREAD_GRAYSCALE)  # 영상 읽기
if image is None: raise Exception("영상 파일 읽기 오류")
    
hist = cv.calcHist([image], [0], None, [32], [0, 256])
hist_img = draw_histo(hist)

cv.imshow("image", image)
cv.imshow("hist_img", hist_img)
cv.waitKey(0)
cv.destroyAllWindows()

# 빼기연산 후 히스토그램 보기
image = cv.subtract(image, 50);
hist = cv.calcHist([image], [0], None, [32], [0, 256])
hist_img = draw_histo(hist)
cv.imshow("image", image)
cv.imshow("hist_img", hist_img)
cv.waitKey(0)

##############################################################
# 히스토그램 plot 이용 표시
# pip install matplotlib
from matplotlib import pyplot as plt
colors = ("gray")
plt.figure()
plt.title("Gray Histogram")
plt.xlabel("Bins")
plt.ylabel("Pixel")
features = []
 
image = cv.imread("./flower.jpg", cv.IMREAD_GRAYSCALE)  # 영상 읽기
hist = cv.calcHist([image], [0], None, [256], [0, 256])
cv.normalize(hist, hist, 0, 256, cv.NORM_MINMAX)
features.extend(hist)
 
plt.plot(hist, color = colors)
plt.xlim([0, 256])
 
print("size: %d " % (np.array(features).flatten().shape))
plt.show()

######## 3채널 컬러 히스토그램 pot 이용 표시
image = cv.imread("./flower.jpg", cv.IMREAD_COLOR)  # 영상 읽기
chans = cv.split(image)
colors = ("b", "g", "r")
plt.figure()
plt.title("Color Histogram")
plt.xlabel("Bins")
plt.ylabel("Pixel")
features = []
 
for(chan, color) in zip(chans, colors):
    hist = cv.calcHist([chan], [0], None, [256], [0, 256])
    features.extend(hist)
 
    plt.plot(hist, color = color)
    plt.xlim([0, 256])
 
print("size: %d " % (np.array(features).flatten().shape))
plt.show()
cv.destroyAllWindows()


##############################################################
# 채널변환 HSV 히스토그램
image = cv.imread("./logo.jpg", cv.IMREAD_COLOR)  # 영상 읽기
def draw_histo_hue(hist, shape=(200, 256,3)):
    hist_img = np.full(shape, 255, np.uint8)
    cv.normalize(hist, hist, 0, shape[0], cv.NORM_MINMAX)    

    gap = hist_img.shape[1] / hist.shape[0] 
    for i, h in enumerate(hist):
        x, w = int(round(i * gap)), int(round(gap))
        
        cv.rectangle(hist_img, (x,0,w, int(h) ), (0,0,0) , cv.FILLED)

    return cv.flip(hist_img, 0)

hsv_img = cv.cvtColor(image, cv.COLOR_BGR2HSV)                     # BGR 컬러 -> HSV 컬러     
hue_hist = cv.calcHist( [hsv_img], [0], None, [18], [0,180])        # Hue 채널 히스토그램 계산
hue_hist_img = draw_histo_hue(hue_hist, (200, 360, 3)) 
cv.imshow("image", image)
cv.imshow("hsv_img", hsv_img)
cv.imshow("hue_hist_img", hue_hist_img)
cv.waitKey(0)
cv.destroyAllWindows()

## inrange 붉은 계열 추출
hsv_img = cv.cvtColor(image, cv.COLOR_BGR2HSV)                     # BGR 컬러 -> HSV 컬러  
chans_hsv = cv.split(hsv_img)
inrangemask1 = cv.inRange(chans_hsv[0], 0, 30);
inrangemask2 = cv.inRange(chans_hsv[0], 165, 180);
inrangemask = inrangemask1 + inrangemask2
crop = cv.bitwise_and(image, cv.cvtColor(inrangemask, cv.COLOR_GRAY2BGR));
cv.imshow("image", image)
cv.imshow("chans_hsv", chans_hsv[0])
cv.imshow("inrangemask", inrangemask)
cv.imshow("crop", crop)
cv.waitKey(0)
cv.destroyAllWindows()

##############################################################
# 캐니엣지
def onTrackbar(th):															# 트랙바 콜백 함수
	rep_edge = cv.Canny(rep_gray, th, th*2)						                # 캐니 에지 검출
	h, w = image.shape[:2]
	cv.rectangle(rep_edge, (0, 0, w, h), 255, -1)    						    # 흰색 사각형 그리기
	color_edge = cv.bitwise_and(rep_image, rep_image, mask=rep_edge)
	cv.imshow("color edge", color_edge)

image = cv.imread("./flower.jpg", cv.IMREAD_COLOR)
if image is None: raise Exception("영상파일 읽기 오류")

th = 50
rep_image = cv.repeat(image, 1, 2)                      	# 가로 반복 복사
rep_gray = cv.cvtColor(rep_image, cv.COLOR_BGR2GRAY)    	# 명암도 영상 변환

cv.namedWindow("color edge", cv.WINDOW_AUTOSIZE)    		# 윈도우 생성
cv.createTrackbar("Canny th", "color edge", th, 100, onTrackbar)	# 콜백 함수 등록
onTrackbar(th)																					# 콜백 함수 첫 실행
cv.waitKey(0)

#############################################################
# 알약 영역 인식

image_read = cv.imread("./drug/1.png", cv.IMREAD_COLOR)

image  = cv.boxFilter(image_read, ddepth=-1, ksize=(10, 10))

image_roi = image[0:10, 0:image.shape[1] - 1]
channels = cv.split(image_roi)
avg_b, avg_g, avg_r = (cv.mean(channels[0]) , cv.mean(channels[1]), cv.mean(channels[2]))

mean_image = np.zeros(image.shape, np.uint8)
mean_image[:,:,0] = int(avg_b[0])
mean_image[:,:,1] = int(avg_g[0])
mean_image[:,:,2] = int(avg_r[0])

abs = cv.absdiff(image, mean_image);
ret, th_img = cv.threshold(abs, 30, 255, cv.THRESH_BINARY)  # 영상 이진화

th_channels = cv.split(th_img)
th_mask = th_channels[0] + th_channels[1] + th_channels[2]

morp_mask = np.array([[0, 1, 0],                         # 마스크 초기화
                      [1, 1, 1],
                      [0, 1, 0]]).astype("uint8")

morp_mask = np.ones((5,5), np.uint8)
th_morped = cv.morphologyEx(th_mask, cv.MORPH_DILATE, morp_mask)
th_morped = cv.morphologyEx(th_morped, cv.MORPH_ERODE, morp_mask)

th_morped_color = cv.cvtColor(th_morped, cv.COLOR_GRAY2BGR)
drug_crop = cv.copyTo(image_read, th_morped_color)

cv.imshow("image_read", image_read)
cv.imshow("image", image)
cv.imshow("mean_image", mean_image)
cv.imshow("abs", abs)
cv.imshow("th", th_img)
cv.imshow("th_mask", th_mask)
cv.imshow("th_morped", th_morped)
cv.imshow("th_mask", th_mask)
cv.imshow("drug_crop", drug_crop)
cv.waitKey(0)
cv.destroyAllWindows()

###################
#추출 후보영역 추출
# contour 외곽선 추출방법
contour_image = th_morped_color.copy()
contours, hierarchy = cv.findContours(th_morped, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_NONE) 
cv.drawContours(contour_image, contours, -1, (0, 0, 255), 1)

object_list_mask = list()
object_list = list()
object_list_gray = list()
for i in range(len(contours)):
    x, y, w, h = cv.boundingRect(contours[i])
    crop_mask = th_morped[y:y+h, x:x+w]
    crop_image = drug_crop[y:y+h, x:x+w]
    crop_image_gray = cv.cvtColor(crop_image, cv.COLOR_BGR2GRAY)
    object_list_mask.append(crop_mask)
    object_list.append(crop_image)
    object_list_gray.append(crop_image_gray)
    cv.imshow("object_list_mask " + str(i), object_list_mask[i])
    cv.imshow("object_list " + str(i), object_list[i])

cv.imshow("contour_image", contour_image)
cv.waitKey(0)
cv.destroyAllWindows()

####################
# 글자와 배경 분리
n_idx = 0
drug_blur  = cv.boxFilter(object_list_gray[n_idx], ddepth=-1, ksize=(30, 30))
bg_avg, bg_stddev = cv.meanStdDev(drug_blur, mask = object_list_mask[n_idx])
print(bg_avg, bg_stddev)
thr_adp = cv.adaptiveThreshold(object_list_gray[n_idx], 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY, 31, 20)
ret, thr_inv = cv.threshold(thr_adp, 1, 255, cv.THRESH_BINARY_INV)

contours, hierarchy = cv.findContours(thr_inv, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_NONE) 
center_y = int(object_list[n_idx].shape[0] / 2)

for i in range(len(contours)):
    x, y, w, h = cv.boundingRect(contours[i])
    if w < 10 or y < 10:
        continue
    M = cv.moments(contours[i])
    cX = int(M['m10'] / M['m00'])
    cY = int(M['m01'] / M['m00'])
    if cY > center_y - 20 and cY < center_y + 20:
        cv.rectangle(object_list[n_idx], (x,y), (x+w, y+h), (0, 0, 255), 2);

cv.imshow("object_list[n_idx]", object_list[n_idx])
cv.imshow("object_list_gray[n_idx]", object_list_gray[n_idx])
cv.imshow("object_list_mask[n_idx]", object_list_mask[n_idx])
cv.imshow("drug_blur", drug_blur)
cv.imshow("thr_adp", thr_adp)
cv.imshow("thr_inv", thr_inv)

cv.waitKey(0)
cv.destroyAllWindows()