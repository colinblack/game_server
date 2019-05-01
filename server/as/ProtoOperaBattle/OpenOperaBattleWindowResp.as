package ProtoOperaBattle {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoOperaBattle.OperaBattleCPPAll;
	import ProtoOperaBattle.MemoryOperaBattleRecordCPPAll;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class OpenOperaBattleWindowResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const OPERABATTLES:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoOperaBattle.OpenOperaBattleWindowResp.operabattles", "operabattles", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOperaBattle.OperaBattleCPPAll; });

		public var operabattles:ProtoOperaBattle.OperaBattleCPPAll;

		/**
		 *  @private
		 */
		public static const RECORDS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoOperaBattle.OpenOperaBattleWindowResp.records", "records", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOperaBattle.MemoryOperaBattleRecordCPPAll; });

		public var records:ProtoOperaBattle.MemoryOperaBattleRecordCPPAll;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.operabattles);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.records);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var operabattles$count:uint = 0;
			var records$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (operabattles$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenOperaBattleWindowResp.operabattles cannot be set twice.');
					}
					++operabattles$count;
					this.operabattles = new ProtoOperaBattle.OperaBattleCPPAll();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.operabattles);
					break;
				case 2:
					if (records$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenOperaBattleWindowResp.records cannot be set twice.');
					}
					++records$count;
					this.records = new ProtoOperaBattle.MemoryOperaBattleRecordCPPAll();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.records);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
