package ProtoYellowVip {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoYellowVip.YellowVipCPP;
	import ProtoYellowVip.FinalRewardCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class GetNewerGiftResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoYellowVip.GetNewerGiftResp.reward", "reward", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoYellowVip.FinalRewardCPP; });

		public var reward:ProtoYellowVip.FinalRewardCPP;

		/**
		 *  @private
		 */
		public static const YELLOWVIP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoYellowVip.GetNewerGiftResp.yellowvip", "yellowvip", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoYellowVip.YellowVipCPP; });

		public var yellowvip:ProtoYellowVip.YellowVipCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.yellowvip);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var reward$count:uint = 0;
			var yellowvip$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetNewerGiftResp.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new ProtoYellowVip.FinalRewardCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.reward);
					break;
				case 2:
					if (yellowvip$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetNewerGiftResp.yellowvip cannot be set twice.');
					}
					++yellowvip$count;
					this.yellowvip = new ProtoYellowVip.YellowVipCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.yellowvip);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
