package ProtoMine {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.RewardItemCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class MineKingdomMinerRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const OP_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineKingdomMinerRewardResp.op_ts", "opTs", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var opTs:uint;

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoMine.MineKingdomMinerRewardResp.exp", "exp", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.RewardItemCPP; });

		public var exp:DataCommon.RewardItemCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.opTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.exp);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var op_ts$count:uint = 0;
			var exp$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (op_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineKingdomMinerRewardResp.opTs cannot be set twice.');
					}
					++op_ts$count;
					this.opTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineKingdomMinerRewardResp.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = new DataCommon.RewardItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.exp);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
