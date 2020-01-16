package generators;

import types.EType;

public abstract class Generator {
    abstract double getRandomValue();
    abstract public EType getMessageType();

    double[] generatorParams;

    public int getFibbonachiNumber(){
        return (int)getRandomValue();
    }

    public int getPowBase(){
        return (int)getRandomValue();
    }

    public int getPowValue(){
        return (int)getRandomValue();
    }

    public int getArraySize(){
        return (int)getRandomValue();
    }

    public double[] getArray(int arrayLength){
        double[] array = new double[arrayLength];

        for(int i=0; i<arrayLength; i++){
            array[i] = getRandomValue();
        }
        return array;
    }

    public int getMessagesCount(){
        return (int)getRandomValue();
    }

    public long getMessagesInterval(){
        return (long)getRandomValue()*100;
    }
}
