setwd("C:\\Users\\hyunho\\source\\ai\\Project4\\Project4")
w0<-read.csv("0_weight.csv",header=F)
w1<-read.csv("1_weight.csv",header=F)
w2<-read.csv("2_weight.csv",header=F)
err<-read.csv("errNum.csv",header=F)

data<-cbind(w0,w1,w2)
names(data)<-(c("w0","w1","w2"))
slope<-c(0)
intercept<-c(0)
data<-cbind(data,slope,intercept)
data=transform(data,slope=-w1/w2)
data=transform(data,intercept=-w0/w2)
data

x=c(0,0,1,1)
y=c(0,1,0,1)
plot(x,y, main="PLOT",sub = "type=p",xlim=c(-2.5,3.5),ylim=c(-2.5,3.5),xlab="x-lab",ylab="y-lab",type="p",pch=1,cex=2)
abline(h = 0:1.5, v = 0:1.5, col = "Gray", lty=3)
points(x=c(0),y=c(0),col="blue",cex=2)
points(x=c(1),y=c(0),col="blue",cex=2)
points(x=c(0),y=c(1),col="blue",cex=2)
for(i in 1:nrow(data)){
  abline(a=data$intercept[i],b=data$slope[i],col="red")
  Sys.sleep(1)
}
#abline(a=w$intercept[nrow(w)],b=w$slope[nrow(w)],col="red")

names(err)<-(c("errNum"))
x<-1:nrow(err)
y<-err$errNum
plot(x,y,ylim=c(0,4),xlab="Iter",ylab="errNum",type='l')
