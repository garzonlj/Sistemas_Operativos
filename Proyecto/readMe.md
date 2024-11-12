# Sistema de Comunicación entre Publicador y Suscriptores

## Descripción

Este proyecto implementa un sistema de comunicación mediante tuberías FIFO (First-In, First-Out), permitiendo que un **publicador** envíe noticias a **suscriptores** interesados en categorías específicas. Los suscriptores pueden recibir noticias relacionadas con las categorías a las que se han suscrito, y el publicador distribuye las noticias a través de un sistema basado en pipes.

## Funcionalidades

- **Publicador**: Envía noticias a los suscriptores interesados en categorías específicas.
- **Suscriptores**: Se suscriben a categorías específicas y reciben noticias a través de pipes exclusivos.
- **Tuberías FIFO**: Se utilizan pipes (tuberías) para la comunicación entre el publicador y los suscriptores, de modo que los mensajes se transmiten de manera eficiente.
- **Gestión de actividad**: El sistema monitorea la actividad de los publicadores y suscriptores, y cierra la emisión de noticias después de un período sin actividad.

## Requisitos

- Sistema operativo Linux o compatible.
- Compilador `gcc` (o similar).
- Permisos para crear pipes en el directorio de ejecución.

## Instalación

1. Clona o descarga el repositorio.

