# Ejercicio 4

Leo empezó a hacer limpieza de su PC y encontró sus proyectos de 1º año. Empezó a revisar el código fuente y vio cosas que no le parecía que estuvieran bien, pero como él todavía no cursó Sistemas Operativos, no tiene los conocimientos del alumno, por eso se pide que analicen el archivo Errores.c y encuentren los errores que detecten.

Para poder resolver este ejercicio si se utiliza Eclipse es necesario deshabilitar los warnings, ya que sino este nos mostrará sus sugerencias. 

Para esto hay que hacer botón derecho sobre el proyecto y luego ir a **Properties->C/C++ Build->Settings** en la sección **Compiler->Warnings** destildamos show all warnings (**-Wall**) y tildamos inhibit all warnings (**-w**). Esto evitará que nos muestre los warnings que detectarían  la mayoría de los errores en el código. Además hay que ir a **Window->Preferences->C/C++->Code Analysis** y destildar todas las warnings. 

**Esto debe hacerse antes de agregar los source al proyecto ya que automáticamente el Eclipse analiza y marca las warnings.**
