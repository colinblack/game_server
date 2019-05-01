package DataCommon {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.EquipSubsCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class EquipmentCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EQUD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataCommon.EquipmentCPP.equd", "equd", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var equd:uint;

		/**
		 *  @private
		 */
		public static const EQID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataCommon.EquipmentCPP.eqid", "eqid", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var eqid:uint;

		/**
		 *  @private
		 */
		public static const NUM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataCommon.EquipmentCPP.num", "num", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var num:uint;

		/**
		 *  @private
		 */
		public static const DELTIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataCommon.EquipmentCPP.deltime", "deltime", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var deltime:uint;

		/**
		 *  @private
		 */
		public static const HEROID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataCommon.EquipmentCPP.heroid", "heroid", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var heroid:uint;

		/**
		 *  @private
		 */
		public static const STAR:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("DataCommon.EquipmentCPP.star", "star", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var star:uint;

		/**
		 *  @private
		 */
		public static const ISSOLD:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("DataCommon.EquipmentCPP.issold", "issold", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var issold:Boolean;

		/**
		 *  @private
		 */
		public static const BORNVAL:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("DataCommon.EquipmentCPP.bornval", "bornval", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var bornval:Array = [];

		/**
		 *  @private
		 */
		public static const SUBS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("DataCommon.EquipmentCPP.subs", "subs", (10 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipSubsCPP; });

		[ArrayElementType("DataCommon.EquipSubsCPP")]
		public var subs:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.equd);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.eqid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.num);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.deltime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.star);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.issold);
			for (var bornval$index:uint = 0; bornval$index < this.bornval.length; ++bornval$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.bornval[bornval$index]);
			}
			for (var subs$index:uint = 0; subs$index < this.subs.length; ++subs$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 10);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.subs[subs$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var equd$count:uint = 0;
			var eqid$count:uint = 0;
			var num$count:uint = 0;
			var deltime$count:uint = 0;
			var heroid$count:uint = 0;
			var star$count:uint = 0;
			var issold$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (equd$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipmentCPP.equd cannot be set twice.');
					}
					++equd$count;
					this.equd = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (eqid$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipmentCPP.eqid cannot be set twice.');
					}
					++eqid$count;
					this.eqid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (num$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipmentCPP.num cannot be set twice.');
					}
					++num$count;
					this.num = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (deltime$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipmentCPP.deltime cannot be set twice.');
					}
					++deltime$count;
					this.deltime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (heroid$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipmentCPP.heroid cannot be set twice.');
					}
					++heroid$count;
					this.heroid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (star$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipmentCPP.star cannot be set twice.');
					}
					++star$count;
					this.star = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (issold$count != 0) {
						throw new flash.errors.IOError('Bad data format: EquipmentCPP.issold cannot be set twice.');
					}
					++issold$count;
					this.issold = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 9:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.bornval);
						break;
					}
					this.bornval.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 10:
					this.subs.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new DataCommon.EquipSubsCPP()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
