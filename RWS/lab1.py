# Наложение водяного знака
img_np = np.array(img)
img_wat = img_wat.transpose(Image.ROTATE_90)
wat_np = np.array(img_wat)
for i in range(img_np.shape[0]):
    for j in range(img_np.shape[1]):
        pixel = img_np[i, j]
        for k in range(3):
            if (pixel[k] > (255 * betta)):
                pixel[k] = wat_np[i, j][k]
        img.putpixel((j, i), (pixel[0], pixel[1], pixel[2]) )
axes[2, 0].imshow(img)
axes[2, 0].set_title("Наложение водяного знака")
3.9 Наложение шума. 
Описание алгоритма 
Задаю img_noise_1 и img_noise_2 как пустые изображения размера исходного изображения. pixel_color – это значение цветов пикселя. factor – сила шума. В цикле перебираю каждый пиксель и прибавляю случайное значение от -factor до factor. Далее проверяю, что значение не выходит за пределы значений (от 0 до 255). После вычисляю ошибку в пикселе вычитая из значений исходного пикселя значения получившегося, складываю все цветовые каналы в пикселе и делю на 255, чтобы получить значение от 0 до 1. Потом задаю получившийся пиксель в изображение. Нахожу значение ошибки в изображении, получившуюся сумму делю на количество пикселей (размер изображения) и умножаю на 100.
Текст программы
# Наложение шума
er_1 = 0
er_2 = 0
factor = 50
img_np = np.array(img)
img_noise_1 = Image.new('RGB', (img_np.shape[1], img_np.shape[0]), (0,0,0))
img_noise_2 = Image.new('RGB', (img_np.shape[1], img_np.shape[0]), (0,0,0))
pixel_color = [0, 0, 0]

for i in range (img_np.shape[0]):
    for j in range (img_np.shape[1]):
        pixel = img_np[i,j]

        # Шум 1
        for k in range(3):
            pixel_color[k] = int(pixel[k] + np.random.randint(-factor, factor))
            if (pixel_color[k] > 255):
                pixel_color[k] = 255
            if (pixel_color[k] < 0):
                pixel_color[k] = 0
        er_1 += sum(abs(pixel - pixel_color)) / 255
        img_noise_1.putpixel((j, i), (pixel_color[0], pixel_color[1], pixel_color[2]))
        
        # Шум 2
        for k in range(3):
            pixel_color[k] = int(pixel[k] + np.random.randint(-(factor + pixel[k]), (factor + pixel[k])))
            if (pixel_color[k] > 255):
                pixel_color[k] = 255
            if (pixel_color[k] < 0):
                pixel_color[k] = 0
        er_2 += sum(abs(pixel - pixel_color)) / 255
        img_noise_2.putpixel((j, i), (pixel_color[0], pixel_color[1], pixel_color[2]))

print(f"Шум: 1){(er_1 / (img_np.shape[0] * img_np.shape[1]) * 100)}%, 2){(er_2 / (img_np.shape[0] * img_np.shape[1]) * 100)}%")
axes[2, 1].imshow(img_noise_1)
axes[2, 2].imshow(img_noise_2)
3.10 Вывод изображения на экран. 
Текст программы
plt.show()
Полный Код
# Вариант 3
import numpy as np
from PIL import Image
from matplotlib import pyplot as plt


# Данные
angle = 10
color = [0, 100, 0]
shift = 0
shuffle = ['g', 'r', 'g']
color_filter = 'b,r'
alpha = 0.3
betta = 0.2

fig, axes = plt.subplots(3, 3) #сетка

# Открытие изображения
img = Image.open("img.jpg")
img_wat = Image.open("wat.jpg")
axes[0, 0].imshow(img)
axes[0, 0].set_title("Открытие изображения")

# Поворот изображения
img = img.rotate(angle=angle)
axes[0, 1].imshow(img)
axes[0, 1].set_title("Поворот изображения")

# Рисование креста
img_np = np.array(img)
y = img_np.shape[0] // 2
x = img_np.shape[1] // 2 + shift
img_np[y-5:y+5, :, :] = color
img_np[:, x-5:x+5, :] = color
axes[0, 2].imshow(img_np)
axes[0, 2].set_title("Рисование креста")

# Изменение цветовой карты
r, g, b = img.split() #разбиваем rgb на массивы
color_map = []
for i in shuffle:
    if (i == 'r'):
        color_map.append(r)
    elif (i == 'g'):
        color_map.append(g)
    else:
        color_map.append(b)
img = Image.merge('RGB', color_map) #Объединение 3-х каналов
axes[1, 0].imshow(img)
axes[1, 0].set_title("Изменение цветовой карты")

# Поворот изображения
img = img.transpose(Image.ROTATE_90)
axes[1, 1].imshow(img)
axes[1, 1].set_title("Поворот изображения")

# Замена буквы канала (color_filter) на номер, чтобы меньше писать
if (color_filter == 'r'):
    color_filter = 0
elif (color_filter == 'g'):
    color_filter = 1
else:
    color_filter = 2

# Обнуление канала
img_np = np.array(img)
for i in range(img_np.shape[0]):
    for j in range(img_np.shape[1]):
        pixel = img_np[i, j]
        if (pixel[color_filter] > (255 * alpha)):
            pixel[color_filter] = 0
            img.putpixel((j, i), (pixel[0], pixel[1], pixel[2]))
axes[1, 2].imshow(img)
axes[1, 2].set_title("Обнуление канала")

# Наложение водяного знака
img_np = np.array(img)
img_wat = img_wat.transpose(Image.ROTATE_90)
wat_np = np.array(img_wat)
for i in range(img_np.shape[0]):
    for j in range(img_np.shape[1]):
        pixel = img_np[i, j]
        for k in range(3):
            if (pixel[k] > (255 * betta)):
                pixel[k] = wat_np[i, j][k]
        img.putpixel((j, i), (pixel[0], pixel[1], pixel[2]) )
axes[2, 0].imshow(img)
axes[2, 0].set_title("Наложение водяного знака")
# Наложение шума
er_1 = 0
er_2 = 0
factor = 50
img_np = np.array(img)
img_noise_1 = Image.new('RGB', (img_np.shape[1], img_np.shape[0]), (0,0,0))
img_noise_2 = Image.new('RGB', (img_np.shape[1], img_np.shape[0]), (0,0,0))
pixel_color = [0, 0, 0]

for i in range (img_np.shape[0]):
    for j in range (img_np.shape[1]):
        pixel = img_np[i,j]

        # Шум 1
        for k in range(3):
            pixel_color[k] = int(pixel[k] + np.random.randint(-factor, factor))
            if (pixel_color[k] > 255):
                pixel_color[k] = 255
            if (pixel_color[k] < 0):
                pixel_color[k] = 0
        er_1 += sum(abs(pixel - pixel_color)) / 255
        img_noise_1.putpixel((j, i), (pixel_color[0], pixel_color[1], pixel_color[2]))
        
        # Шум 2
        for k in range(3):
            pixel_color[k] = int(pixel[k] + np.random.randint(-(factor + pixel[k]), (factor + pixel[k])))
            if (pixel_color[k] > 255):
                pixel_color[k] = 255
            if (pixel_color[k] < 0):
                pixel_color[k] = 0
        er_2 += sum(abs(pixel - pixel_color)) / 255
        img_noise_2.putpixel((j, i), (pixel_color[0], pixel_color[1], pixel_color[2]))

print(f"Шум: 1){(er_1 / (img_np.shape[0] * img_np.shape[1]) * 100)}%, 2){(er_2 / (img_np.shape[0] * img_np.shape[1]) * 100)}%")
axes[2, 1].imshow(img_noise_1)
axes[2, 2].imshow(img_noise_2)

plt.show()
