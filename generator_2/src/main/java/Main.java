import generators.Generator;
import generators.Uniform;
import types.EType;
import types.ModeType;
import java.io.FileOutputStream;
import java.io.IOException;

/*  TODO:
     -> разобраться с тестом на генерацию числа в эксп законе
 */

public class Main {
    private static ModeType modeValue;
    private static double[] params = new double[2];
    private static Generator generator;
    private static int minMsgCount = 0;

    public static ModeType getBySpelling(String spelling) {
        if (ModeType.EXPONENTIAL.getSpelling().equals(spelling)) {
            return ModeType.EXPONENTIAL;
        } else if (ModeType.NORMAL.getSpelling().equals(spelling)) {
            return ModeType.NORMAL;
        }
        return ModeType.UNIFORM;
    }

    public static void parseOptions(String[] args) throws Exception {
        for(int i = 0; i < args.length; i++){
            if ("--mode".equals(args[i])) {
                i++;
                modeValue = getBySpelling(args[i]);
            } else if ("--param".equals(args[i])) {
                i++;
                params[0] = Double.parseDouble(args[i]);
                if(modeValue != ModeType.EXPONENTIAL) {
                    i++;
                    params[1] = Double.parseDouble(args[i]);
                }
            }  else if ("--msg".equals(args[i])) {
                i++;
                minMsgCount = Integer.parseInt(args[i]);
            } else {
                throw new Exception("Wrong generator options");
            }
        }
    }

    public static TMessage.TMessageProto getMessage() throws Exception {
        if(generator != null ){
            EType messageType = generator.getMessageType();
            MessageCreator messageCreator = new MessageCreator();

            switch (messageType){
                case FIBONACCI:
                    return messageCreator.getMessage(messageType, generator.getFibbonacciNumber());
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

    public static void main(String[] args) {
        try{
            parseOptions(args);
            generator = Generator.initGenerator(modeValue, params);

            int i =0 ;
            int messageCount = minMsgCount + generator.getMessagesCount();

            while (i < messageCount){
                TMessage.TMessageProto message = getMessage();
                System.out.println("message type "  + message.getType());
                FileOutputStream fos = new FileOutputStream("hub");
                message.writeTo(fos);
                fos.close();

                Thread.sleep(generator.getMessagesInterval());
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
