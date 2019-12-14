setwd("C:\\Users\\hyunho\\source\\ai\\Project6\\Project6\\donut")
in0<-read.csv("input0.csv",header=F)
in1<-read.csv("input1.csv",header=F)
w0<-read.csv("weight0.csv",header=F)
w1<-read.csv("weight1.csv",header=F)
b<-read.csv("bias.csv",header=F)
err<-read.csv("err.csv",header=F)

data<-cbind(in0,in1,w0,w1,b)
names(data)<-(c("in0","in1","w0","w1","b"))
slope<-c(0)
intercept<-c(0)
data<-cbind(data,slope,intercept)
data=transform(data,slope=-w0/w1)
data=transform(data,intercept=-b/w1)
data

x=c(0,0,1,1)
y=c(0,1,0,1)
plot(data$in0[1],data$in1[1], main="PLOT",sub = "type=p",xlim=c(-2.5,3.5),ylim=c(-2.5,3.5),xlab="x-lab",ylab="y-lab",type="p",pch=1,cex=2)
abline(h = 0:1.5, v = 0:1.5, col = "Gray", lty=3)
points(x=c(0),y=c(0),col="blue",cex=2)
points(x=c(1),y=c(0),col="blue",cex=2)
points(x=c(0),y=c(1),col="blue",cex=2)
abline(a=data$intercept[1],b=data$slope[1],col="red")
for(i in 2300:nrow(data)){
  plot(data$in0[i],data$in1[i], main="PLOT",sub = "type=p",xlim=c(-2.5,3.5),ylim=c(-2.5,3.5),xlab="x-lab",ylab="y-lab",type="p",pch=1,cex=2)
  abline(h = 0:1.5, v = 0:1.5, col = "Gray", lty=3)
  abline(a=data$intercept[i],b=data$slope[i],col="red")
  Sys.sleep(2)
}
for(i in 1:nrow(data)){
  if(i%%270==0){
    plot(data$in0[i],data$in1[i], main="PLOT",sub = "type=p",xlim=c(-2.5,3.5),ylim=c(-2.5,3.5),xlab="x-lab",ylab="y-lab",type="p",pch=1,cex=2)
    abline(h = 0:1.5, v = 0:1.5, col = "Gray", lty=3)
    abline(a=data$intercept[i],b=data$slope[i],col="red")
    Sys.sleep(2)
  }
}
#abline(a=w$intercept[nrow(w)],b=w$slope[nrow(w)],col="red")

names(err)<-(c("err"))
x<-1:nrow(err)
y<-err$err
plot(x,y,ylim=c(0,2.5),xlab="Iter",ylab="err",type='l')
