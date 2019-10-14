setwd("C:\\Users\\hyunho\\Shiny\\study\\3-2\\univ_class\\Ai\\°úÁ¦\\#3\\donut4")
input<-read.csv("input.csv",header=F)
weight<-read.csv("w_layer.csv",header=F)
bias<-read.csv("bias.csv",header=F)
err<-read.csv("err.csv",header=F)

data<-cbind(input,weight,bias)
data
data<-data[-c(5,12,16)]
names(data)<-(c("in00","in10","in01","in11","w000","w100","w010","w110","w001","w101","b00","b10","b01"))
slope00<-c(0)
intercept00<-c(0)
data<-cbind(data,slope00,intercept00)
data=transform(data,slope00=-w000/w100)
data=transform(data,intercept00=-b00/w100)
slope10<-c(0)
intercept10<-c(0)
data<-cbind(data,slope10,intercept10)
data=transform(data,slope10=-w010/w110)
data=transform(data,intercept10=-b10/w110)
slope01<-c(0)
intercept01<-c(0)
data<-cbind(data,slope01,intercept01)
data=transform(data,slope01=-w001/w101)
data=transform(data,intercept01=-b01/w101)
data

x=c(0,0,1,1,0.5,1,0,0.5,0.5)
y=c(0,1,0,1,1,0.5,0.5,0,0.5)
# node00 whole input
for(i in 1:nrow(data)){
  plot(x,y, main="PLOT",sub = "type=p",xlim=c(-2.5,3.5),ylim=c(-2.5,3.5),xlab="x-lab",ylab="y-lab",type="p",pch=1,cex=2)
  abline(h = 0:1.5, v = 0:1.5, col = "Gray", lty=3)
  points(x=c(0.5),y=c(0.5),col="green",cex=2)
  if(i%%9==1){
    abline(a=data$intercept00[i],b=data$slope00[i],col="red")
    Sys.sleep(0.1)
  }
}
# node10 whole input
for(i in 1:nrow(data)){
  plot(x,y, main="PLOT",sub = "type=p",xlim=c(-2.5,3.5),ylim=c(-2.5,3.5),xlab="x-lab",ylab="y-lab",type="p",pch=1,cex=2)
  abline(h = 0:1.5, v = 0:1.5, col = "Gray", lty=3)
  points(x=c(0.5),y=c(0.5),col="green",cex=2)
  if(i%%9==1){
    abline(a=data$intercept10[i],b=data$slope10[i],col="blue")
    Sys.sleep(0.1)
  }
}
# node00 with node10 whole input
for(i in 1:nrow(data)){
  plot(x,y, main="PLOT",sub = "type=p",xlim=c(-2.5,3.5),ylim=c(-2.5,3.5),xlab="x-lab",ylab="y-lab",type="p",pch=1,cex=2)
  abline(h = 0:1.5, v = 0:1.5, col = "Gray", lty=3)
  points(x=c(0.5),y=c(0.5),col="green",cex=2)
  if(i%%9==1){
    abline(a=data$intercept00[i],b=data$slope00[i],col="red")
    abline(a=data$intercept10[i],b=data$slope10[i],col="blue")
    Sys.sleep(0.1)
  }
}

# node00 with node10 whole input
for(i in 10000:nrow(data)-8){
  if(i%%9==1){
    plot(c(5),c(5),main="PLOT",sub = "type=p",xlim=c(-2.5,3.5),ylim=c(-2.5,3.5),xlab="x-lab",ylab="y-lab");
    abline(h = 0:1.5, v = 0:1.5, col = "Gray", lty=3);
    points(x=data$in01[i],y=data$in11[i],col="black",cex=1)
    points(x=data$in01[i+1],y=data$in11[i+1],col="black",cex=1)
    points(x=data$in01[i+2],y=data$in11[i+2],col="black",cex=1)
    points(x=data$in01[i+3],y=data$in11[i+3],col="black",cex=1)
    points(x=data$in01[i+4],y=data$in11[i+4],col="black",cex=1)
    points(x=data$in01[i+5],y=data$in11[i+5],col="black",cex=1)
    points(x=data$in01[i+6],y=data$in11[i+6],col="black",cex=1)
    points(x=data$in01[i+7],y=data$in11[i+7],col="black",cex=1)
    points(x=data$in01[i+8],y=data$in11[i+8],col="green",cex=2)
    abline(a=data$intercept01[i],b=data$slope01[i],col="red")
    Sys.sleep(0.1)
  }
}
#abline(a=w$intercept[nrow(w)],b=w$slope[nrow(w)],col="red")

names(err)<-(c("err"))
x<-1:nrow(err)
y<-err$err
plot(x,y,ylim=c(0,2.5),xlab="Iter",ylab="err",type='l')

