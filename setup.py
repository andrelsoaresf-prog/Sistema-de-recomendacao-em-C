from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "resenha",
        ["bindings.cpp", "Similaridade.cpp",
         "Recomendacao.cpp", "CSR.cpp"], 
        cxx_std=17,
    ),
]

setup(
    name="resenha",
    version="0.1.0",
    description="importando arquivos do projeto",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)