import importlib
import sys
import ctypes
import enum


def validate_structs() -> None:
    """Validates the structures in the structures package. This is used to ensure that everything is generated correctly."""
    try:
        sys.path.insert(0, "./gen")
        import structures
    except ImportError as ex:
        print("Error: structures can't be imported, something went wrong.", file=sys.stderr, flush=True)
        raise ex

    for module_name in structures.__all__:
        try:
            print(f"Validating {module_name}... " + " " * (40 - len(module_name)), end="")
            module = importlib.import_module(f"structures.{module_name}")
            obj = getattr(module, module_name)
            if type(obj) == type(ctypes.Structure):
                _ = obj()
            elif type(obj) == type(ctypes.Union):
                _ = obj()
            elif type(obj) == type(enum.IntEnum):
                for value in obj:
                    _ = obj(value)
            else:
                raise NotImplementedError(f"Unknown type: {type(obj)} for {module_name}.{module_name}")
            print(f"{type(obj)}: Success.", end="\r")
        except ModuleNotFoundError as ex:
            print(f"\nError: {module_name}.{module_name} can't be created, something went wrong.", file=sys.stderr, flush=True)
            raise ex
    msg = f"Done validating {len(structures.__all__)} structures!"
    print(f"{msg}{' ' * (100 - len(msg))}")
          
if __name__ == "__main__":
    validate_structs()
    print("Done validating structures package.")