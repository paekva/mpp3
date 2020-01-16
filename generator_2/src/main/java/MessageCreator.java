import types.EType;

public class MessageCreator {

    TMessage.TMessageProto getMessage(EType messageType, int Fibbonacci){
        return TMessage.TMessageProto.newBuilder()
                .setType(messageType.index())
                .setSize(1)
                .addData(Fibbonacci)
                .build();
    }

    TMessage.TMessageProto getMessage(EType messageType, int powBase, int powValue){
        return TMessage.TMessageProto.newBuilder()
                .setType(messageType.index())
                .setSize(2)
                .addData(powBase)
                .addData(powValue)
                .build();
    }

    TMessage.TMessageProto getMessage(EType messageType, int size, double[] array){
        TMessage.TMessageProto.Builder builder= TMessage.TMessageProto.newBuilder()
                .setType(messageType.index())
                .setSize(1 + size)
                .addData(size);

        for(int i=0; i< size; i++){
            builder.addData((int)array[i]); // TODO: fix lose of precision
        }

        return builder.build();
    }

    TMessage.TMessageProto getMessage(EType messageType){
        return TMessage.TMessageProto.newBuilder()
                .setType(messageType.index())
                .setSize(0)
                .build();
    }
}
