# Guía de Contribución

¡Gracias por tu interés en contribuir al NarcosLife Framework! Este documento proporciona pautas para contribuir al proyecto.

## 🤝 Cómo Contribuir

### Reportar Bugs

Si encuentras un bug, por favor crea un issue con:

- **Título descriptivo** del problema
- **Pasos para reproducir** el bug
- **Comportamiento esperado** vs **comportamiento actual**
- **Versión** de Arma Reforger y del framework
- **Logs** relevantes (si están disponibles)
- **Capturas de pantalla** (si es aplicable)

### Sugerir Mejoras

Para sugerir nuevas características:

1. Verifica que no exista ya un issue similar
2. Crea un nuevo issue con etiqueta "enhancement"
3. Describe detalladamente la característica propuesta
4. Explica por qué sería útil para el framework
5. Proporciona ejemplos de uso si es posible

### Pull Requests

#### Proceso

1. **Fork** el repositorio
2. **Crea una rama** desde `main`:
   ```bash
   git checkout -b feature/mi-nueva-caracteristica
   ```
3. **Realiza tus cambios** siguiendo las guías de estilo
4. **Commit** tus cambios con mensajes descriptivos:
   ```bash
   git commit -m "Add: Sistema de misiones dinámicas"
   ```
5. **Push** a tu fork:
   ```bash
   git push origin feature/mi-nueva-caracteristica
   ```
6. **Abre un Pull Request** con descripción detallada

#### Guías para Pull Requests

- Mantén los cambios **enfocados y específicos**
- Actualiza la **documentación** si es necesario
- Añade **comentarios** donde el código sea complejo
- Sigue el **estilo de código** existente
- Asegúrate de que el código **compile sin errores**

## 📝 Guías de Estilo

### Código

#### Nombres de Clases y Archivos

```c
// Usar prefijo NL_ para todas las clases del framework
class NL_MiNuevaClase

// Archivos deben coincidir con el nombre de la clase
// Archivo: NL_MiNuevaClase.c
```

#### Convenciones de Nomenclatura

```c
// Clases: PascalCase con prefijo NL_
class NL_WeaponSystem

// Métodos: PascalCase
void ProcessTransaction()

// Variables miembro: m_xNombre donde x es el tipo
protected int m_iPlayerId;          // i = integer
protected float m_fMoney;           // f = float
protected string m_sName;           // s = string
protected bool m_bIsActive;         // b = boolean
protected array<int> m_aList;       // a = array
protected map<int, string> m_mMap;  // m = map
protected ref NL_Class m_Object;    // Sin prefijo para objetos

// Variables locales: camelCase
int playerId;
float currentMoney;
```

#### Comentarios

```c
//------------------------------------------------------------------------------------------------
// Título de Sección o Clase
// Descripción de lo que hace esta clase o método
//------------------------------------------------------------------------------------------------
class NL_Example
{
    //------------------------------------------------------------------------------------------------
    // Comentario para método público
    void PublicMethod()
    {
        // Comentarios inline para lógica compleja
        if (condition)
        {
            // Explica por qué, no qué
            DoSomething();
        }
    }
}
```

#### Estructura de Archivos

```c
//------------------------------------------------------------------------------------------------
// Encabezado con descripción del archivo
//------------------------------------------------------------------------------------------------

// Imports si son necesarios

//------------------------------------------------------------------------------------------------
// Clase Principal
//------------------------------------------------------------------------------------------------
class NL_MainClass
{
    // Atributos
    [Attribute()]
    protected type m_attribute;
    
    // Variables miembro
    protected type m_variable;
    
    // Constructor
    void NL_MainClass()
    {
    }
    
    // Métodos públicos
    void PublicMethod()
    {
    }
    
    // Métodos protegidos
    protected void ProtectedMethod()
    {
    }
}

//------------------------------------------------------------------------------------------------
// Clases Auxiliares (si las hay)
//------------------------------------------------------------------------------------------------
class NL_HelperClass
{
}
```

### Documentación

#### README y Documentos

- Usa **Markdown** para formatear
- Incluye **ejemplos de código** cuando sea relevante
- Mantén las **secciones organizadas**
- Actualiza el **índice** si añades secciones

#### Comentarios en Código

- Documenta **el propósito**, no el funcionamiento obvio
- Explica **decisiones de diseño** no triviales
- Documenta **parámetros y valores de retorno** de métodos públicos
- Usa **TODO** para trabajo pendiente:
  ```c
  // TODO: Implementar validación adicional
  ```

## 🏗️ Estructura del Proyecto

Al añadir nuevos archivos, respeta la estructura existente:

```
Addons/NarcosLifeFramework/
├── Scripts/
│   ├── Game/              # Lógica principal del juego
│   ├── Components/        # Componentes de entidades
│   ├── Systems/           # Sistemas independientes
│   └── UI/                # UI y gestión de interfaz
├── Configs/               # Archivos de configuración
├── Prefabs/               # Prefabs del juego
├── Worlds/                # Mundos/mapas
└── UI/                    # Layouts de UI
```

## 🧪 Testing

Aunque no hay tests automatizados actualmente:

1. **Prueba tus cambios** en Arma Reforger Workbench
2. **Verifica** que no hay errores en la consola
3. **Documenta** los pasos de prueba en el PR
4. **Verifica compatibilidad** con cambios existentes

## 📋 Checklist para Pull Requests

Antes de enviar tu PR, verifica:

- [ ] El código sigue las guías de estilo del proyecto
- [ ] He añadido/actualizado comentarios donde es necesario
- [ ] He actualizado la documentación relevante
- [ ] He probado los cambios en Arma Reforger
- [ ] No hay errores de compilación
- [ ] Los cambios son compatibles con el código existente
- [ ] El PR tiene una descripción clara de los cambios

## 📞 Comunicación

- **Issues**: Para bugs, features y discusiones
- **Pull Requests**: Para contribuciones de código
- **Discussions**: Para preguntas generales y ayuda

## 🎯 Áreas de Contribución

Algunas áreas donde las contribuciones son especialmente bienvenidas:

- **Sistema de Drogas**: Plantaciones, procesamiento, venta
- **Misiones Dinámicas**: Sistema de misiones generadas
- **Persistencia**: Integración con base de datos
- **UI**: Mejoras de interfaz de usuario
- **Optimización**: Mejoras de rendimiento
- **Documentación**: Tutoriales, guías, traducciones
- **Ejemplos**: Más ejemplos de uso del framework

## 📜 Código de Conducta

- Sé **respetuoso** con otros contribuidores
- Acepta **críticas constructivas**
- Enfócate en lo **mejor para el proyecto**
- Mantén un **ambiente acogedor** para todos

## ❓ Preguntas

Si tienes preguntas sobre cómo contribuir:

1. Revisa la documentación existente
2. Busca en issues cerrados
3. Abre un nuevo issue con etiqueta "question"

## 🙏 Agradecimientos

Toda contribución, grande o pequeña, es apreciada y ayuda a mejorar el framework para toda la comunidad.

¡Gracias por contribuir al NarcosLife Framework!
