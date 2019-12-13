import java.io.FileOutputStream;
import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException, InterruptedException {
        int i = 0;

        while(i<30){
            System.out.println("hello");
            TMessage.TMessageProto message = TMessage.TMessageProto.newBuilder()
                    .setType(i%3)
                    .setSize(1)
                    .addData(1)
                    .build();

            FileOutputStream fos = new FileOutputStream("hub");
            message.writeTo(fos);
            fos.close();
            Thread.sleep(1000);
            i++;
        }

        TMessage.TMessageProto message = TMessage.TMessageProto.newBuilder()
                .setType(3)
                .setSize(1)
                .addData(1)
                .build();

        FileOutputStream fos = new FileOutputStream("hub");
        message.writeTo(fos);
    }
}
