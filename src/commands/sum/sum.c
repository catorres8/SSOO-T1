
// Funcion sum se encarga de sumar los argumentos entregados y 
// retornar el  mensaje respectivo
char sum(float a, float b)
{
    char mensaje[];
    
    float c;
    c = a + b;

    mensaje = "La suma de %f y %f es %f", a, b, c //Modificar a una correcta forma
    
    return mensaje
}