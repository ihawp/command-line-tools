from PIL import Image

frame1 = Image.open("w.webp")
frame2 = frame1.rotate(90)

frame1.save(
	"animated.webp",
	save_all=True,
	append_iamge=[frame2],
	duration=500,
	loop=0
)
