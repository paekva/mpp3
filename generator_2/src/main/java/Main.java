import generators.Exponential;
import generators.Generator;
import generators.Normal;
import generators.Uniform;
import types.EType;
import java.io.FileOutputStream;
import java.io.IOException;

public class Main {
    private static String modeValue = "";
    private static double[] params = new double[2];
    private static Generator generator;

    private static void parseOptions(String[] args) throws Exception {
        for(int i = 0; i < args.length; i++){
            if ("--mode".equals(args[i])) {
                i++;
                modeValue = args[i];
            } else if ("--param".equals(args[i])) {
                i++;
                params[0] = Double.parseDouble(args[i]);
                i++;
                if(!modeValue.equals("exp")) {
                    params[1] = Double.parseDouble(args[i]);
                }
            } else {
                throw new Exception("Wrong generator options");
            }
        }
    }

    private static TMessage.TMessageProto getMessage() throws Exception {
        if(generator != null ){
            EType messageType = generator.getMessageType();
            MessageCreator messageCreator = new MessageCreator();

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
        if ("exp".equals(modeValue)) {
            generator = new Exponential(params);
        } else if ("normal".equals(modeValue)) {
            generator = new Normal(params);
        } else {
            generator = new Uniform(params);
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        try{
            parseOptions(args);
            initGenerator();
            int i =0 ;
            int messageCount = generator.getMessagesCount();
            Uniform generatorSec = new Uniform(params);

            while (i < messageCount){
                TMessage.TMessageProto message = getMessage();
                System.out.println("message type "  + message.getType());
                FileOutputStream fos = new FileOutputStream("hub");
                message.writeTo(fos);
                fos.close();

                Thread.sleep(generatorSec.getMessagesInterval());
                i++;
            }

            FileOutputStream fos = new FileOutputStream("hub");
            MessageCreator messageCreator = new MessageCreator();
            messageCreator.getMessage(EType.STOP).writeTo(fos);
            fos.close();

        } catch (Exception e){
            System.out.println(e.getMessage());
        }
    }
}
