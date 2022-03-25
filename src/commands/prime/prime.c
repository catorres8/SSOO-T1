
// Un numero es primo si solo es divisible por 1 y por si mismo
void is_prime(int a)
{
    char mensaje[];

    // Caso de numero invalido
    if a < 2)
    {
        mensaje = "El numero entregado no es primo";
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
        mensaje = ""
        for (int i = 2; i < a; i++)
        {
            if (a % i == 0)
            {
                mensaje = "El numero entregado no es primo";
            }
            
        }

        if (mensaje == "")
        {
            mensaje = "El numero entregado es primo";
        }
        
        
    }

    printf("%c\n", mensaje);
}

// codigo reducible*