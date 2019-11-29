public class MessageCreator {

    TMessagesProto.TMessage getMessage(EType messageType, int fibbonachi){
        return TMessagesProto.TMessage.newBuilder()
                .setType(messageType.index())
                .setSize(1)
                .addData(fibbonachi)
                .build();
    }

    TMessagesProto.TMessage getMessage(EType messageType, int powBase, int powValue){
        return TMessagesProto.TMessage.newBuilder()
                .setType(messageType.index())
                .setSize(2)
                .addData(powBase)
                .addData(powValue)
                .build();
    }

    TMessagesProto.TMessage getMessage(EType messageType, int size, double[] array){
        TMessagesProto.TMessage.Builder builder= TMessagesProto.TMessage.newBuilder()
                .setType(messageType.index())
                .setSize(1 + size)
                .addData(size);

        for(int i=0; i< size; i++){
            builder.addData((int)array[i]); // TODO: fix lose of precision
        }

        return builder.build();
    }

    TMessagesProto.TMessage getMessage(EType messageType){
        return TMessagesProto.TMessage.newBuilder()
                .setType(messageType.index())
                .setSize(0)
                .build();
    }
}
