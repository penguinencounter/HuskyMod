import re


with open("input.txt") as f:
    d = f.read()
ename = input("enum name? ")

collection = []
counter = 0
for line in d.split("\n"):
    line_st = line.strip()
    match_ = re.search(r'(\w+)(?:\s*=\s*(\d+))?,?', line_st)
    if not match_:
        print(f"Error in line {line_st}")
        continue
    name = match_.group(1)
    if match_.group(2):
        value = match_.group(2)
    else:
        value = counter
        counter += 1
    collection.append((name, value))

template_top = f"""
from ghidra.program.model.data import EnumDataType
enum = EnumDataType("{ename}", 8)
dtm = currentProgram.getDataTypeManager()
"""

template_bottom = f"""
dtm.addDataType(enum, None)
"""

template_middle = ""
for name, value in collection:
    template_middle += f'enum.add("{name}", {value})\n'

with open("output.py", "a") as f:
    f.write(f"\n\n# Add enum: {ename}")
    f.write(template_top + template_middle + template_bottom)
    f.write(f"\n")

print("Done")