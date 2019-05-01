package ProtoAttackHarbor {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import flash.utils.ByteArray;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class CountryRankCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const KINGDOM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoAttackHarbor.CountryRankCPP.kingdom", "kingdom", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var kingdom:uint;

		/**
		 *  @private
		 */
		public static const WRECKAGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoAttackHarbor.CountryRankCPP.wreckage", "wreckage", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var wreckage:uint;

		/**
		 *  @private
		 */
		public static const TRUMP_UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoAttackHarbor.CountryRankCPP.trump_uid", "trumpUid", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var trumpUid:uint;

		/**
		 *  @private
		 */
		public static const TRUMP_NAME:FieldDescriptor_TYPE_BYTES = new FieldDescriptor_TYPE_BYTES("ProtoAttackHarbor.CountryRankCPP.trump_name", "trumpName", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var trumpName:flash.utils.ByteArray;

		/**
		 *  @private
		 */
		public static const TRUMP_WRECKAGE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoAttackHarbor.CountryRankCPP.trump_wreckage", "trumpWreckage", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var trumpWreckage:uint;

		/**
		 *  @private
		 */
		public static const RANK:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoAttackHarbor.CountryRankCPP.rank", "rank", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rank:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.kingdom);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.wreckage);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.trumpUid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_BYTES(output, this.trumpName);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.trumpWreckage);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rank);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var kingdom$count:uint = 0;
			var wreckage$count:uint = 0;
			var trump_uid$count:uint = 0;
			var trump_name$count:uint = 0;
			var trump_wreckage$count:uint = 0;
			var rank$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (kingdom$count != 0) {
						throw new flash.errors.IOError('Bad data format: CountryRankCPP.kingdom cannot be set twice.');
					}
					++kingdom$count;
					this.kingdom = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (wreckage$count != 0) {
						throw new flash.errors.IOError('Bad data format: CountryRankCPP.wreckage cannot be set twice.');
					}
					++wreckage$count;
					this.wreckage = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (trump_uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: CountryRankCPP.trumpUid cannot be set twice.');
					}
					++trump_uid$count;
					this.trumpUid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (trump_name$count != 0) {
						throw new flash.errors.IOError('Bad data format: CountryRankCPP.trumpName cannot be set twice.');
					}
					++trump_name$count;
					this.trumpName = com.netease.protobuf.ReadUtils.read_TYPE_BYTES(input);
					break;
				case 5:
					if (trump_wreckage$count != 0) {
						throw new flash.errors.IOError('Bad data format: CountryRankCPP.trumpWreckage cannot be set twice.');
					}
					++trump_wreckage$count;
					this.trumpWreckage = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (rank$count != 0) {
						throw new flash.errors.IOError('Bad data format: CountryRankCPP.rank cannot be set twice.');
					}
					++rank$count;
					this.rank = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
