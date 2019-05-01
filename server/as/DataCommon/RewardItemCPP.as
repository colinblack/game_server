package DataCommon {
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
	public dynamic final class RewardItemCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const VALUE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataCommon.RewardItemCPP.value", "value", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var value:uint;

		/**
		 *  @private
		 */
		public static const TOTAL_VALUE:FieldDescriptor_TYPE_UINT64 = new FieldDescriptor_TYPE_UINT64("DataCommon.RewardItemCPP.total_value", "totalValue", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var totalValue:UInt64;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.value);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT64(output, this.totalValue);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var value$count:uint = 0;
			var total_value$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (value$count != 0) {
						throw new flash.errors.IOError('Bad data format: RewardItemCPP.value cannot be set twice.');
					}
					++value$count;
					this.value = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (total_value$count != 0) {
						throw new flash.errors.IOError('Bad data format: RewardItemCPP.totalValue cannot be set twice.');
					}
					++total_value$count;
					this.totalValue = com.netease.protobuf.ReadUtils.read_TYPE_UINT64(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
