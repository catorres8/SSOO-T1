
// Un numero es primo si solo es divisible por 1 y por si mismo
char is_prime(int numero)
{
    char mensaje[];

    // Caso de numero invalido
    if (numero < 2)
    {
        mensaje = "El numero entregado no es valido";
    }

    // Caso de numero par distinto de 2
    else if (a != 2 && a % 2 == 0)
    {
        mensaje = "El numero entregado no es primo";
    }
    
    // Caso de a = 2
    else if (a == 2)
    {
        mensaje = "El numero entregado es primo";
    }
    
    // Caso de numero no par
    else
    { 
        // Bucle que determina si el numero es divisible por algun numero
        // entre 2 y n-1
        for (int i = 2; i < a; i++)
        {
            if (numero % i == 0)
            {
                mensaje = "El numero entregado no es primo";
            }
            
        }

        if (mensaje == "vacio") //Corregir
        {
            mensaje = "El numero entregado es primo";
        }
        
        
    }

    return mensaje
}

// codigo reducible*