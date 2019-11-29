import types.EType;

public class MessageCreator {

    TMessageProto.TMessage getMessage(EType messageType, int fibbonachi){
        return TMessageProto.TMessage.newBuilder()
                .setType(messageType.index())
                .setSize(1)
                .addData(fibbonachi)
                .build();
    }

    TMessageProto.TMessage getMessage(EType messageType, int powBase, int powValue){
        return TMessageProto.TMessage.newBuilder()
                .setType(messageType.index())
                .setSize(2)
                .addData(powBase)
                .addData(powValue)
                .build();
    }

    TMessageProto.TMessage getMessage(EType messageType, int size, double[] array){
        TMessageProto.TMessage.Builder builder= TMessageProto.TMessage.newBuilder()
                .setType(messageType.index())
                .setSize(1 + size)
                .addData(size);

        for(int i=0; i< size; i++){
            builder.addData((int)array[i]); // TODO: fix lose of precision
        }

        return builder.build();
    }

    TMessageProto.TMessage getMessage(EType messageType){
        return TMessageProto.TMessage.newBuilder()
                .setType(messageType.index())
                .setSize(0)
                .build();
    }
}
