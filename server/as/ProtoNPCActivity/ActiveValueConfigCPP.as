package ProtoNPCActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataConfig.RewardConfigCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ActiveValueConfigCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const VALUE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.ActiveValueConfigCPP.value", "value", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var value:uint;

		/**
		 *  @private
		 */
		public static const REWARD:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.ActiveValueConfigCPP.reward", "reward", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataConfig.RewardConfigCPP; });

		[ArrayElementType("DataConfig.RewardConfigCPP")]
		public var reward:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.value);
			for (var reward$index:uint = 0; reward$index < this.reward.length; ++reward$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward[reward$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var value$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (value$count != 0) {
						throw new flash.errors.IOError('Bad data format: ActiveValueConfigCPP.value cannot be set twice.');
					}
					++value$count;
					this.value = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					this.reward.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new DataConfig.RewardConfigCPP()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
