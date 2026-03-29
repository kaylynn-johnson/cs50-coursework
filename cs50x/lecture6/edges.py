from PIL import Image, ImageFilter

before = Image.open("stadium.bmp")
after = before.filter(ImageFilter.FIND_EDGES)
after.save("out_edges.bmp")
