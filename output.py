

# Add enum: fpioa_pull_t
from ghidra.program.model.data import EnumDataType
enum = EnumDataType("fpioa_pull_t", 8)
dtm = currentProgram.getDataTypeManager()
enum.add("FPIOA_PULL_NONE", 0)
enum.add("FPIOA_PULL_DOWN", 1)
enum.add("FPIOA_PULL_UP", 2)
enum.add("FPIOA_PULL_MAX", 3)

dtm.addDataType(enum, None)

