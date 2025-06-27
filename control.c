#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Repuesto
{
    char nombre[50];
    int cantidad;
    float precio;
};

// Prototipos
void Iniciarlizarproductos(struct Repuesto repuestos[], int *cantidadRepuestos);
void imprimirProductos(struct Repuesto repuestos[], int *cantidadRepuestos);
void agregarProducto(struct Repuesto repuestos[], int *cantidadRepuestos);
void eliminarProducto(struct Repuesto repuestos[], int *cantidadRepuestos);
void modificarProducto(struct Repuesto repuestos[], int *cantidadRepuestos);
void buscarProducto(struct Repuesto repuestos[], int *cantidadRepuestos);
void guardarProductos(struct Repuesto repuestos[], int cantidadRepuestos);
void menuProductos(struct Repuesto repuestos[], int *cantidadRepuestos);
void menuVentas(struct Repuesto repuestos[], int *cantidadRepuestos);
void Ventas(struct Repuesto repuestos[], int *cantidadRepuestos);
void verFacturas();
void buscarFactura();
void retornoProducto(struct Repuesto repuestos[], int *cantidadRepuestos);
void verStock(struct Repuesto repuestos[], int *cantidadRepuestos);
void verGanancias(struct Repuesto repuestos[], int cantidadRepuestos); // NUEVO PROTOTIPO

int main()
{
    int seguir = 1;
    struct Repuesto repuestos[100];
    int cantidadRepuestos = 0;
    int productosInicializados = 0;

    while (seguir)
    {
        int opcion;
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Inicializar productos\n");
        printf("2. Relacionado productos\n");
        printf("3. Ventas\n");
        printf("4. Stock\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            Iniciarlizarproductos(repuestos, &cantidadRepuestos);
            productosInicializados = 1;
            break;
        case 2:
            if (!productosInicializados) {
                printf("Debe inicializar los productos antes de usar esta opcion.\n");
                break;
            }
            menuProductos(repuestos, &cantidadRepuestos);
            break;
        case 3:
            if (!productosInicializados) {
                printf("Debe inicializar los productos antes de usar esta opcion.\n");
                break;
            }
            menuVentas(repuestos, &cantidadRepuestos);
            break;
        case 4:
            if (!productosInicializados) {
                printf("Debe inicializar los productos antes de usar esta opcion.\n");
                break;
            }
            verStock(repuestos, &cantidadRepuestos);
            break;
        case 5:
            seguir = 0;
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida.\n");
        }
    }

    return 0;
}

void menuProductos(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    int opcion;
    do
    {
        printf("\n--- SUBMENU PRODUCTOS ---\n");
        printf("1. Imprimir productos\n");
        printf("2. Agregar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Modificar producto\n");
        printf("5. Buscar producto\n");
        printf("6. Volver al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            imprimirProductos(repuestos, cantidadRepuestos);
            break;
        case 2:
            agregarProducto(repuestos, cantidadRepuestos);
            break;
        case 3:
            eliminarProducto(repuestos, cantidadRepuestos);
            break;
        case 4:
            modificarProducto(repuestos, cantidadRepuestos);
            break;
        case 5:
            buscarProducto(repuestos, cantidadRepuestos);
            break;
        case 6:
            printf("Volviendo al menu principal...\n");
            break;
        default:
            printf("Opcion invalida.\n");
        }
    } while (opcion != 6);
}

void menuVentas(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    int opcion;
    do {
        printf("\n--- SUBMENU VENTAS ---\n");
        printf("1. Realizar venta\n");
        printf("2. Ver facturas\n");
        printf("3. Buscar factura\n");
        printf("4. Retorno de producto\n");
        printf("5. Volver al menu principal\n");
        printf("6. Ver ganancias y unidades vendidas\n"); // NUEVA OPCIÓN
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            Ventas(repuestos, cantidadRepuestos);
            break;
        case 2:
            verFacturas();
            break;
        case 3:
            buscarFactura();
            break;
        case 4:
            retornoProducto(repuestos, cantidadRepuestos);
            break;
        case 5:
            printf("Volviendo al menu principal...\n");
            break;
        case 6:
            verGanancias(repuestos, *cantidadRepuestos);
            break;
        default:
            printf("Opcion invalida.\n");
        }
    } while (opcion != 5);
}

void Iniciarlizarproductos(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    strcpy(repuestos[0].nombre, "Frenos");
    repuestos[0].cantidad = 10;
    repuestos[0].precio = 50.0;

    strcpy(repuestos[1].nombre, "Llantas");
    repuestos[1].cantidad = 20;
    repuestos[1].precio = 80.0;

    strcpy(repuestos[2].nombre, "Chasis");
    repuestos[2].cantidad = 5;
    repuestos[2].precio = 200.0;

    strcpy(repuestos[3].nombre, "Pastillas");
    repuestos[3].cantidad = 15;
    repuestos[3].precio = 30.0;

    *cantidadRepuestos = 4;
    guardarProductos(repuestos, *cantidadRepuestos);
    printf("Productos inicializados exitosamente.\n");
}

void guardarProductos(struct Repuesto repuestos[], int cantidadRepuestos)
{
    FILE *file = fopen("repuestos.dat", "wb+");
    if (file == NULL)
    {
        printf("Error al abrir el archivo para guardar los productos.\n");
        return;
    }

    fwrite(repuestos, sizeof(struct Repuesto), cantidadRepuestos, file);
    fclose(file);
    printf("Productos guardados exitosamente.\n");
}

void imprimirProductos(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    FILE *file = fopen("repuestos.dat", "rb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo para cargar los productos.\n");
        return;
    }

    *cantidadRepuestos = fread(repuestos, sizeof(struct Repuesto), 100, file);
    fclose(file);
    printf("Productos cargados exitosamente. Cantidad: %d\n", *cantidadRepuestos);
    printf("\n=== LISTA DE REPUESTOS ===\n");
    for (int i = 0; i < *cantidadRepuestos; i++)
    {
        printf("Nombre: %s, Cantidad: %d, Precio: %.2f\n", repuestos[i].nombre, repuestos[i].cantidad, repuestos[i].precio);
    }
}

void agregarProducto(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    if (*cantidadRepuestos >= 100)
    {
        printf("No se pueden agregar mas productos. Limite alcanzado.\n");
        return;
    }

    struct Repuesto nuevoRepuesto;
    printf("Ingrese el nombre del nuevo repuesto: ");
    scanf("%s", nuevoRepuesto.nombre);
    printf("Ingrese la cantidad del nuevo repuesto: ");
    scanf("%d", &nuevoRepuesto.cantidad);
    printf("Ingrese el precio del nuevo repuesto: ");
    scanf("%f", &nuevoRepuesto.precio);

    repuestos[*cantidadRepuestos] = nuevoRepuesto;
    (*cantidadRepuestos)++;
    guardarProductos(repuestos, *cantidadRepuestos);
    printf("Producto agregado exitosamente.\n");
}

void eliminarProducto(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    char nombre[50];
    printf("Ingrese el nombre del repuesto a eliminar: ");
    scanf("%s", nombre);

    for (int i = 0; i < *cantidadRepuestos; i++)
    {
        if (strcmp(repuestos[i].nombre, nombre) == 0)
        {
            for (int j = i; j < *cantidadRepuestos - 1; j++)
            {
                repuestos[j] = repuestos[j + 1];
            }
            (*cantidadRepuestos)--;
            guardarProductos(repuestos, *cantidadRepuestos);
            printf("Producto eliminado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void modificarProducto(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    char nombre[50];
    printf("Ingrese el nombre del repuesto a modificar: ");
    scanf("%s", nombre);

    for (int i = 0; i < *cantidadRepuestos; i++)
    {
        if (strcmp(repuestos[i].nombre, nombre) == 0)
        {
            printf("Ingrese la nueva cantidad: ");
            scanf("%d", &repuestos[i].cantidad);
            printf("Ingrese el nuevo precio: ");
            scanf("%f", &repuestos[i].precio);
            guardarProductos(repuestos, *cantidadRepuestos);
            printf("Producto modificado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void buscarProducto(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    char nombre[50];
    printf("Ingrese el nombre del repuesto a buscar: ");
    scanf("%s", nombre);

    for (int i = 0; i < *cantidadRepuestos; i++)
    {
        if (strcmp(repuestos[i].nombre, nombre) == 0)
        {
            printf("Producto encontrado: Nombre: %s, Cantidad: %d, Precio: %.2f\n", repuestos[i].nombre, repuestos[i].cantidad, repuestos[i].precio);
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void Ventas(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    char nombre[50], cliente[50];
    int cantidadVenta;
    char opcion;
    int encontrado, totalProductosVendidos = 0;
    float totalVenta = 0.0;

    printf("Ingrese el nombre del cliente: ");
    scanf("%s", cliente);

    srand(time(NULL));
    int numeroFactura = rand() % 100000 + 1000;

    do {
        encontrado = 0;
        printf("Ingrese el nombre del repuesto a vender: ");
        scanf("%s", nombre);

        for (int i = 0; i < *cantidadRepuestos; i++)
        {
            if (strcmp(repuestos[i].nombre, nombre) == 0)
            {
                printf("Ingrese la cantidad a vender: ");
                scanf("%d", &cantidadVenta);

                if (cantidadVenta <= 0)
                {
                    printf("Cantidad invalida.\n");
                    break;
                }

                if (repuestos[i].cantidad >= cantidadVenta)
                {
                    repuestos[i].cantidad -= cantidadVenta;
                    totalVenta += cantidadVenta * repuestos[i].precio;
                    totalProductosVendidos += cantidadVenta;
                    guardarProductos(repuestos, *cantidadRepuestos);
                    printf("Venta realizada. Quedan %d unidades de %s.\n", repuestos[i].cantidad, repuestos[i].nombre);
                }
                else
                {
                    printf("No hay suficiente stock para realizar la venta.\n");
                }
                encontrado = 1;
                break;
            }
        }
        if (!encontrado)
        {
            printf("Producto no encontrado.\n");
        }

        printf("¿Desea vender otro producto? (s/n): ");
        scanf(" %c", &opcion);
    } while (opcion == 's' || opcion == 'S');

    float iva = totalVenta * 0.10f;
    float totalConIVA = totalVenta + iva;

    // Imprimir factura
    printf("\n======= FACTURA =======\n");
    printf("Factura Nro: %d\n", numeroFactura);
    printf("Cliente: %s\n", cliente);
    printf("Total productos vendidos: %d\n", totalProductosVendidos);
    printf("Subtotal: $%.2f\n", totalVenta);
    printf("IVA (10%%): $%.2f\n", iva);
    printf("TOTAL: $%.2f\n", totalConIVA);
    printf("=======================\n");

    // Guardar la venta completa en ventas.dat
    FILE *ventasFile = fopen("ventas.dat", "a");
    if (ventasFile != NULL) {
        fprintf(ventasFile, "Factura: %d | Cliente: %s | Productos: %d | Subtotal: %.2f | IVA: %.2f | TOTAL: %.2f\n",
            numeroFactura, cliente, totalProductosVendidos, totalVenta, iva, totalConIVA);
        fclose(ventasFile);
    } else {
        printf("Error al abrir el archivo de ventas.\n");
    }
}

void verFacturas()
{
    FILE *ventasFile = fopen("ventas.dat", "r");
    char linea[256];
    if (ventasFile == NULL) {
        printf("No hay facturas registradas.\n");
        return;
    }
    printf("\n=== FACTURAS REGISTRADAS ===\n");
    while (fgets(linea, sizeof(linea), ventasFile)) {
        printf("%s", linea);
    }
    fclose(ventasFile);
}

void buscarFactura()
{
    int numeroFactura;
    char linea[256];
    printf("Ingrese el numero de factura a buscar: ");
    scanf("%d", &numeroFactura);

    FILE *ventasFile = fopen("ventas.dat", "r");
    if (ventasFile == NULL) {
        printf("No hay facturas registradas.\n");
        return;
    }
    int encontrada = 0;
    while (fgets(linea, sizeof(linea), ventasFile)) {
        if (strstr(linea, "Factura:")) {
            int num;
            sscanf(linea, "Factura: %d", &num);
            if (num == numeroFactura) {
                printf("Factura encontrada:\n%s", linea);
                encontrada = 1;
                break;
            }
        }
    }
    if (!encontrada) {
        printf("Factura no encontrada.\n");
    }
    fclose(ventasFile);
}

void retornoProducto(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    int numeroFactura, dias;
    char producto[50];
    int cantidadDevuelta;
    int encontrado = 0;
    int facturaEncontrada = 0;

    printf("Ingrese el numero de factura: ");
    scanf("%d", &numeroFactura);

    // Buscar la factura en ventas.dat
    FILE *ventasFile = fopen("ventas.dat", "r");
    if (ventasFile == NULL) {
        printf("No hay facturas registradas.\n");
        return;
    }
    char linea[256];
    while (fgets(linea, sizeof(linea), ventasFile)) {
        int num;
        if (sscanf(linea, "Factura: %d", &num) == 1 && num == numeroFactura) {
            facturaEncontrada = 1;
            break;
        }
    }
    fclose(ventasFile);

    if (!facturaEncontrada) {
        printf("No existe una factura con ese numero, no se puede devolver el producto.\n");
        return;
    }

    printf("¿Cuantos dias han pasado desde la compra?: ");
    scanf("%d", &dias);

    if (dias > 10) {
        printf("No se puede devolver el producto. Han pasado más de 10 días.\n");
        return;
    }

    printf("Ingrese el nombre del producto a devolver: ");
    scanf("%s", producto);
    printf("Ingrese la cantidad a devolver: ");
    scanf("%d", &cantidadDevuelta);

    for (int i = 0; i < *cantidadRepuestos; i++) {
        if (strcmp(repuestos[i].nombre, producto) == 0) {
            repuestos[i].cantidad += cantidadDevuelta;
            guardarProductos(repuestos, *cantidadRepuestos);
            printf("Producto devuelto exitosamente. Nuevo stock de %s: %d\n", repuestos[i].nombre, repuestos[i].cantidad);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Producto no encontrado en el inventario.\n");
    }
}

void verStock(struct Repuesto repuestos[], int *cantidadRepuestos)
{
    FILE *file = fopen("repuestos.dat", "rb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo para cargar los productos.\n");
        return;
    }

    *cantidadRepuestos = fread(repuestos, sizeof(struct Repuesto), 100, file);
    fclose(file);

    printf("\n=== STOCK DE REPUESTOS ===\n");
    for (int i = 0; i < *cantidadRepuestos; i++)
    {
        printf("Nombre: %s, Cantidad: %d, Precio: %.2f", repuestos[i].nombre, repuestos[i].cantidad, repuestos[i].precio);
        if (repuestos[i].cantidad < 5)
        {
            printf("  --> ¡RECOMENDACION: Reabastecer este producto!");
        }
        printf("\n");
    }
}

void verGanancias(struct Repuesto repuestos[], int cantidadRepuestos)
{
    // Estructura para ventas/facturas
    struct Factura {
        int numeroFactura;
        char cliente[50];
        int productosVendidos;
        float subtotal;
        float iva;
        float total;
    };

    // Arreglo para contar unidades vendidas por producto
    int unidadesVendidas[100] = {0};
    float totalGanancias = 0.0;

    FILE *ventasFile = fopen("ventas.dat", "rb");
    if (ventasFile == NULL) {
        printf("No hay ventas registradas.\n");
        return;
    }

    struct Factura factura;
    while (fread(&factura, sizeof(struct Factura), 1, ventasFile)) {
        totalGanancias += factura.subtotal;
        // Suma total de unidades vendidas (no por producto, pero por factura)
        // Si quieres por producto, necesitas guardar el detalle de cada producto vendido en la factura
        // Aquí solo suma el total de unidades de la factura
        // Puedes mejorar esto si guardas el detalle de cada producto en ventas.dat
        for (int i = 0; i < cantidadRepuestos; i++) {
            // Aquí solo suma si el producto fue vendido, pero no hay detalle por producto en la factura
            // Así que solo suma al primero como ejemplo
            unidadesVendidas[i] += factura.productosVendidos;
            break;
        }
    }
    fclose(ventasFile);

    printf("\n=== GANANCIAS ===\n");
    printf("Total ganado (sin IVA): $%.2f\n", totalGanancias);
    printf("\n=== UNIDADES VENDIDAS (estimado por factura) ===\n");
    for (int i = 0; i < cantidadRepuestos; i++) {
        printf("Producto: %s | Unidades vendidas: %d\n", repuestos[i].nombre, unidadesVendidas[i]);
    }
}
