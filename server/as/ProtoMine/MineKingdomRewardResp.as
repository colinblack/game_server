package ProtoMine {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.UserResourceCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class MineKingdomRewardResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const OP_TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMine.MineKingdomRewardResp.op_ts", "opTs", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var opTs:uint;

		/**
		 *  @private
		 */
		public static const ASSETS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoMine.MineKingdomRewardResp.assets", "assets", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.UserResourceCPP; });

		public var assets:DataCommon.UserResourceCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.opTs);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.assets);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var op_ts$count:uint = 0;
			var assets$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (op_ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineKingdomRewardResp.opTs cannot be set twice.');
					}
					++op_ts$count;
					this.opTs = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (assets$count != 0) {
						throw new flash.errors.IOError('Bad data format: MineKingdomRewardResp.assets cannot be set twice.');
					}
					++assets$count;
					this.assets = new DataCommon.UserResourceCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.assets);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
