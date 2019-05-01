package ProtoNPCActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoNPCActivity.ActiveValueConfigCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class OpenPlatformRewardConfigCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const STARTDAY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.OpenPlatformRewardConfigCPP.startday", "startday", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var startday:uint;

		/**
		 *  @private
		 */
		public static const ACTIVE_VALUE_REWARD:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.OpenPlatformRewardConfigCPP.active_value_reward", "activeValueReward", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.ActiveValueConfigCPP; });

		[ArrayElementType("ProtoNPCActivity.ActiveValueConfigCPP")]
		public var activeValueReward:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.startday);
			for (var activeValueReward$index:uint = 0; activeValueReward$index < this.activeValueReward.length; ++activeValueReward$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.activeValueReward[activeValueReward$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var startday$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (startday$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenPlatformRewardConfigCPP.startday cannot be set twice.');
					}
					++startday$count;
					this.startday = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					this.activeValueReward.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoNPCActivity.ActiveValueConfigCPP()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
