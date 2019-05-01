package ProtoActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import User.RewardBagInfo;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ReceiveDailyKillRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const SHADOW:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.ReceiveDailyKillRewardResp.shadow", "shadow", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var shadow:uint;

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoActivity.ReceiveDailyKillRewardResp.reward", "reward", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return User.RewardBagInfo; });

		public var reward:User.RewardBagInfo;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.shadow);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var shadow$count:uint = 0;
			var reward$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (shadow$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReceiveDailyKillRewardResp.shadow cannot be set twice.');
					}
					++shadow$count;
					this.shadow = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReceiveDailyKillRewardResp.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new User.RewardBagInfo();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.reward);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
