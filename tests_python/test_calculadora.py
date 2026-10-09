import pytest

from prueba import suma, resta, multiplicacion, division

def test_suma():
    assert suma(2, 3) == 5

def test_resta():
    assert resta(5, 3) == 2

def test_multiplicacion():
    assert multiplicacion(2, 3) == 6

def test_division():
    assert division(10, 2) == 5

def test_division_por_cero():
    with pytest.raises(ValueError, match="No se puede dividir por cero"):
        division(10, 0)