package ProtoAttackHarbor {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoAttackHarbor.CountryRankCPPAll;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class OpenAttackWindowResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const COUNTRYRANKS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoAttackHarbor.OpenAttackWindowResp.countryranks", "countryranks", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoAttackHarbor.CountryRankCPPAll; });

		public var countryranks:ProtoAttackHarbor.CountryRankCPPAll;

		/**
		 *  @private
		 */
		public static const REWARD_STATUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoAttackHarbor.OpenAttackWindowResp.reward_status", "rewardStatus", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rewardStatus:uint;

		/**
		 *  @private
		 */
		public static const WRECKAGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoAttackHarbor.OpenAttackWindowResp.wreckage", "wreckage", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var wreckage:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.countryranks);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rewardStatus);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.wreckage);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var countryranks$count:uint = 0;
			var reward_status$count:uint = 0;
			var wreckage$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (countryranks$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenAttackWindowResp.countryranks cannot be set twice.');
					}
					++countryranks$count;
					this.countryranks = new ProtoAttackHarbor.CountryRankCPPAll();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.countryranks);
					break;
				case 2:
					if (reward_status$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenAttackWindowResp.rewardStatus cannot be set twice.');
					}
					++reward_status$count;
					this.rewardStatus = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (wreckage$count != 0) {
						throw new flash.errors.IOError('Bad data format: OpenAttackWindowResp.wreckage cannot be set twice.');
					}
					++wreckage$count;
					this.wreckage = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
