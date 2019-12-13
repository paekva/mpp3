import generators.*;
import types.EType;

import java.io.FileOutputStream;

public class Main {
    private static String modeValue = "";
    private static int notifyInterval = 0;
    private static double[] params = new double[2];
    private static Generator generator;
    private static FileOutputStream fosMetrics;

    private static void parseOptions(String[] args) throws Exception {
        for(int i = 0; i < args.length; i++){
            if ("--mode".equals(args[i])) {
                i++;
                modeValue = args[i];
            } else if ("--param".equals(args[i])) {
                i++;
                params[0] = Double.parseDouble(args[i]);
                i++;
                params[1] = Double.parseDouble(args[i]);
            } else if ("-n".equals(args[i])) {
                i++;
                notifyInterval = Integer.parseInt(args[i]);
            } else {
                throw new Exception("Wrong generator options");
            }
        }
    }

    private static TMessageProto.TMessage getMessage() throws Exception {
        if(generator != null ){
            EType messageType = generator.getMessageType();
            MessageCreator messageCreator = new MessageCreator();

            System.out.println(messageType + "  " + messageType.index());
            switch (messageType){
                case FIBONACCI:
                    return messageCreator.getMessage(messageType, generator.getFibbonachiNumber());
                case POW:
                    return messageCreator.getMessage(messageType, generator.getPowBase(), generator.getPowValue());
                case BUBBLE_SORT_UINT64: {
                    int arrayLength = generator.getArraySize();
                    return messageCreator.getMessage(messageType, arrayLength, generator.getArray(arrayLength));
                }
                default:
                    return messageCreator.getMessage(messageType);
            }
        } else {
            throw new Exception("No generator entity is created");
        }
    }

    private static void initGenerator() {
        if ("uniform".equals(modeValue)) {
            generator = new Uniform(params);
        } else if ("normal".equals(modeValue)) {
            generator = new Normal(params);
        } else {
            generator = new Exponential(params);
        }
    }

    public static void main(String[] args) {
        try{
            /*
            parseOptions(args);
            initGenerator();

            fosMetrics = new FileOutputStream("metrics.txt");
            int messageCount = generator.getMessagesCount();

            FileOutputStream fos = new FileOutputStream("../hub", false);
            for (int i = 0; i < messageCount; i++) {
                getMessage().writeTo(fos);
            }
            MessageCreator messageCreator = new MessageCreator();
            messageCreator.getMessage(EType.STOP).writeTo(fos);
            
            fos.close();
             */

            System.out.println("hel");
            /*
            double[] intervals = generator.getMessagesIntervals(messageCount);
            for(int i=0;i<messageCount;i++) {
                Thread.sleep((long)intervals[i]);
            }
            */

        } catch (Exception e){
            System.out.println(e.getMessage());
        }
    }
}
