package ProtoOperaBattle {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class StartOperaBattleReq extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const GATEID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOperaBattle.StartOperaBattleReq.gateid", "gateid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var gateid:uint;

		/**
		 *  @private
		 */
		public static const DIFFICULTY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoOperaBattle.StartOperaBattleReq.difficulty", "difficulty", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var difficulty:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.gateid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.difficulty);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var gateid$count:uint = 0;
			var difficulty$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (gateid$count != 0) {
						throw new flash.errors.IOError('Bad data format: StartOperaBattleReq.gateid cannot be set twice.');
					}
					++gateid$count;
					this.gateid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (difficulty$count != 0) {
						throw new flash.errors.IOError('Bad data format: StartOperaBattleReq.difficulty cannot be set twice.');
					}
					++difficulty$count;
					this.difficulty = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
