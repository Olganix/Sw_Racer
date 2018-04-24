#!/usr/bin/env python3

import sys
from xml.dom import minidom
import struct

def get_value(s):
  if s[0:2] == '0x':
    return int(s[2:], 16)
  else:
    return int(s)

obj_count = 0
model_count = 0

def face(file, a, b, c):
  print("f %d/%d/%d %d/%d/%d %d/%d/%d" % (a,a,a, b,b,b, c,c,c), file=file)

print("Loading")

# parse an xml file by name
mydoc = minidom.parse(sys.argv[1])

#<?xml version="1.0" encoding="UTF-8" ?>
#<Swr_Model>
#    <path value="out_modelblock.bin" />
#    <Models>
#        <Model Type="Malt">

print("Converting")
Swr_Model = mydoc.documentElement
print(Swr_Model)
models = Swr_Model.getElementsByTagName("Models")[0] #FIXME: Loop over all models?!
print(models)



for model in models.getElementsByTagName("Model"):
  print(model)
  Type = model.attributes['Type'].value

  if Type == 'Track':
    pass
  elif Type == 'Pod':
    pass
  elif Type == 'Malt':



    for malts in model.getElementsByTagName("ListMalt"):

      for malt in malts.getElementsByTagName("Malt"):
        print(malt)

        for Section_3064 in malt.getElementsByTagName("Section_3064"):

          filename = '/tmp/swe1r/foo-%d-%s-%d.obj' % (model_count, malt.attributes['startOffset_id'].value, obj_count)
          obj_count += 1
          if filename != "/tmp/swe1r/foo-0-0x5134-2-0x5-30.obj":
            pass
            #continue

          obj = open(filename, 'w')
          vcount = 0

          for ListSection3 in Section_3064.getElementsByTagName("ListSection3"):

            for Section3 in ListSection3.getElementsByTagName("Section3"):




              typeMode = Section3.getElementsByTagName("typeMode")[0]
              typeMode_s = typeMode.attributes['u16'].value
              typeMode_i = get_value(typeMode_s)
              print(typeMode_s)
              #assert(typeMode_s == '0x5')

              #nbElementV90

              nbElementV52 = Section3.getElementsByTagName("nbElementV52")[0]
              nbElementV52_s = nbElementV52.attributes['u16'].value
              nbElementV52_i = get_value(nbElementV52_s)
              print(nbElementV52_s)


              vbase = vcount

              for ListSection52 in Section3.getElementsByTagName("ListSection52"):

                for Section52 in ListSection52.getElementsByTagName("Section52"):

                  def get_hex(x, field, attrib):
                    value = x.getElementsByTagName(field)[0].attributes[attrib].value                
                    return get_value(value)

                  def u8(x, field):
                    return get_hex(x, field, 'u8')
                  def s8(x, field):
                    return struct.unpack('b', struct.pack('<B', u8(x, field)))[0]
                  def fu8(x, field):
                    return u8(x, field) / 0xFF
                  def fs8(x, field):
                    return s8(x, field) / 0x7F
                  def u16(x, field):
                    return get_hex(x, field, 'u16')
                  def s16(x, field):
                    return struct.unpack('h', struct.pack('<H', u16(x, field)))[0]
                  def fs16(x, field):
                    return s16(x, field) / 0x7FFF

                  x = fs16(Section52, 'unk0')
                  y = fs16(Section52, 'unk2')
                  z = fs16(Section52, 'unk4')
                  zero = u16(Section52, 'unk6')
                  assert(zero == 0x0000)

                  uv_ = u8(Section52, 'unk8')
                  uv__ = u8(Section52, 'unk9')
                  uv___ = u8(Section52, 'unk10')
                  uv____ = u8(Section52, 'unk11')
                  u = (uv__ | (uv_ << 8))
                  u = (struct.unpack('h', struct.pack('<H', u))[0] + 0x8000) / 0xFFFF
                  v = (uv____ | (uv___ << 8))
                  v = (struct.unpack('h', struct.pack('<H', v))[0] + 0x8000) / 0xFFFF

                  nx = fs8(Section52, 'unk12')
                  ny = fs8(Section52, 'unk13')
                  nz = fs8(Section52, 'unk14')

                  specular = fu8(Section52, 'unk15') # Not sure

                  print("# specular??: %f" % (specular), file=obj)
                  print("vn %f %f %f" % (nx, ny, nz), file=obj)
                  print("vt %f %f" % (u, v), file=obj)
                  print("v %f %f %f" % (x, z, y), file=obj)
                  vcount += 1



                #n = len(faces)
                #faces += [n + 1, n + 2, n + 3]


              SectionV90s = Section3.getElementsByTagName("SectionV90")
              print(SectionV90s)
              print()

              #FIXME: This code path is broken

              if typeMode_i == 3:
                assert(len(SectionV90s) == 0)
                n = 0
                count_i = nbElementV52_i
                print(count_i)
                print("Absolute vertex count: %d [triangles]" % count_i)
                assert(count_i % 3 == 0)
                for i in range(count_i // 3):
                  face(obj, vbase + n + 1, vbase + n + 2, vbase + n + 3)
                  n += 3

              elif typeMode_i == 4:
                #FIXME: This code path is slightly broken still?
                assert(len(SectionV90s) == 0)
                n = 0
                count_i = nbElementV52_i
                print(count_i)
                print("Absolute vertex count: %d [quads]" % count_i)
                assert(count_i % 4 == 0)
                for i in range(count_i // 4):
                  #print("f %d %d %d %d" % (vbase + n + 2, vbase + n + 3, vbase + n + 4,  vbase + n + 1), file=obj)
                  face(obj, vbase + n + 2, vbase + n + 3, vbase + n + 4)
                  face(obj, vbase + n + 4, vbase + n + 1,  vbase + n + 2)
                  n += 4

              elif typeMode_i == 5:
                assert(len(SectionV90s) == 1)
                n = 0
                for SectionV90 in SectionV90s:
                  for Value in SectionV90.getElementsByTagName("Value"):
                    count = Value.attributes['u32'].value
                    count_i = struct.unpack('I', struct.pack('>I', get_value(count)))[0]
                    #print(count)
                    print("Batch vertex count: %d" % count_i)
                    for i in range(count_i - 2):
                      face(obj, vbase + n + 1, vbase + n + 2, vbase + n + 3)
                      n += 1
                    n += 2
                #FIXME: Something like: assert(n == nbElementV52_i)

              print("", file=obj)

          if obj_count > 140:
            print(vcount)
            sys.exit(1)


  else:
    print(Type)
    assert(False)
  
  model_count += 1
