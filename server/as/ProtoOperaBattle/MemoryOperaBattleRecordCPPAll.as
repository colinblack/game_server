package ProtoOperaBattle {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoOperaBattle.MemoryBattleRecordCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class MemoryOperaBattleRecordCPPAll extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const BATTLE_RECORD:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoOperaBattle.MemoryOperaBattleRecordCPPAll.battle_record", "battleRecord", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoOperaBattle.MemoryBattleRecordCPP; });

		[ArrayElementType("ProtoOperaBattle.MemoryBattleRecordCPP")]
		public var battleRecord:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var battleRecord$index:uint = 0; battleRecord$index < this.battleRecord.length; ++battleRecord$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.battleRecord[battleRecord$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					this.battleRecord.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoOperaBattle.MemoryBattleRecordCPP()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
