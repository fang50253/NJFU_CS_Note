public class Question4{
    public static int cut(){
        int d=0;
        for(double l=150000;;l=l-l/5,d++){
            System.out.println("l:"+l);
            if(l>=0&&l<1.25){
                break;
            }
        }
        return d;
    }
    public static void main(String[] args){
        System.out.println("Days:"+cut());
    }
}