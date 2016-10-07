import math
import numpy as np
import matplotlib.pyplot as plt
import pylab
import sys

arr = np.genfromtxt("resEj3-fijo.txt") #NOMBRE DEL ARCHIVO!!!
x = [row[2] for row in arr] #tiempo en NS
y = [row[0] for row in arr] #primera columna


def promedio(list):
   return sum(list)/len(list)

def graph(formula, x_range):
    x = np.array(x_range)
    y = eval(formula)
    return y

k = 0
listaPromedio = []
listaPares = []
# print(len(x))
while k < len(x):
  subList = x[k:k+50] #Veces que se corre cada caso
  listaPromedio.append(promedio(subList))
  listaPares.append(y[k])
  k += 50 #Igual que arriba

promedio1NP = np.a<rray(listaPromedio)
casosNP = np.array(listaPares)

cota = '((2x)*(np.log10(x))*1e3)' #lo que tal vez haga falta cambiar es el *1e3 que se agrega para estimar el tiempo en relación a las corridas
grafCota = graph(cota, range(1,200))
deAUno = range(1,200) #este 200 y el de la linea de arriba es hasta que numero en x debería llegar. Debería ser menor a lo que llegan los casos testeados
deAUno = np.array(deAUno)




# medianaX  = mediana(x)
# modaX     = moda(x)

fig = plt.figure()
fig.patch.set_facecolor('white')
ax1 = fig.add_subplot(111)
pylab.plot(casosNP, promedio1NP,'r', label= 'Muchas paredes destructibles')
pylab.plot(deAUno, grafCota,'bo', label= 'Cota de Complejidad')


ax1.set_title("Tiempo con sobre matrices cuadradas de tamaño linealmente creciente")
ax1.set_xlabel('Tamaño de (uno de los lados de) la matriz')
ax1.set_ylabel('Tiempo de procesamiento en ns')

leg = ax1.legend()

leg = plt.legend( loc = 'upper left') #lower right para cambiar la posición de las indicaciones de labels de las lineas

plt.show()
