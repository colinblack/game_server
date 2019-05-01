package ProtoNPCActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoNPCActivity.FinalRewardCPP;
	import ProtoNPCActivity.NPCActivityCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class GetActiveAffairRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.GetActiveAffairRewardResp.reward", "reward", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.FinalRewardCPP; });

		public var reward:ProtoNPCActivity.FinalRewardCPP;

		/**
		 *  @private
		 */
		public static const ACTIVITY:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoNPCActivity.GetActiveAffairRewardResp.activity", "activity", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoNPCActivity.NPCActivityCPP; });

		public var activity:ProtoNPCActivity.NPCActivityCPP;

		/**
		 *  @private
		 */
		public static const CASH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoNPCActivity.GetActiveAffairRewardResp.cash", "cash", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cash:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.activity);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cash);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var reward$count:uint = 0;
			var activity$count:uint = 0;
			var cash$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetActiveAffairRewardResp.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new ProtoNPCActivity.FinalRewardCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.reward);
					break;
				case 2:
					if (activity$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetActiveAffairRewardResp.activity cannot be set twice.');
					}
					++activity$count;
					this.activity = new ProtoNPCActivity.NPCActivityCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.activity);
					break;
				case 3:
					if (cash$count != 0) {
						throw new flash.errors.IOError('Bad data format: GetActiveAffairRewardResp.cash cannot be set twice.');
					}
					++cash$count;
					this.cash = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
