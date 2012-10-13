#!/bin/bash

echo
echo "Agregando archivos al almacen..."

    git add .

echo
echo "Describe tus cambios:"

read mensaje

git commit -m "\""+$mensaje+"\""

echo "Empacando archivos..."
echo

echo "Enviando archivos al repositorio..."

git push https://github.com/andresrcc/opengl/
