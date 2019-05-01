package ProtoMarket {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class MarketCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const REFRESHTIME:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.MarketCPP.refreshtime", "refreshtime", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var refreshtime:uint;

		/**
		 *  @private
		 */
		public static const TYPE1:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.MarketCPP.type1", "type1", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var type1:uint;

		/**
		 *  @private
		 */
		public static const CHARACTER1:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.MarketCPP.character1", "character1", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var character1:uint;

		/**
		 *  @private
		 */
		public static const TYPE2:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.MarketCPP.type2", "type2", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var type2:uint;

		/**
		 *  @private
		 */
		public static const CHARACTER2:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.MarketCPP.character2", "character2", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var character2:uint;

		/**
		 *  @private
		 */
		public static const TYPE3:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.MarketCPP.type3", "type3", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var type3:uint;

		/**
		 *  @private
		 */
		public static const CHARACTER3:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoMarket.MarketCPP.character3", "character3", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var character3:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.refreshtime);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.type1);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.character1);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.type2);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.character2);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.type3);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.character3);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var refreshtime$count:uint = 0;
			var type1$count:uint = 0;
			var character1$count:uint = 0;
			var type2$count:uint = 0;
			var character2$count:uint = 0;
			var type3$count:uint = 0;
			var character3$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (refreshtime$count != 0) {
						throw new flash.errors.IOError('Bad data format: MarketCPP.refreshtime cannot be set twice.');
					}
					++refreshtime$count;
					this.refreshtime = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (type1$count != 0) {
						throw new flash.errors.IOError('Bad data format: MarketCPP.type1 cannot be set twice.');
					}
					++type1$count;
					this.type1 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (character1$count != 0) {
						throw new flash.errors.IOError('Bad data format: MarketCPP.character1 cannot be set twice.');
					}
					++character1$count;
					this.character1 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (type2$count != 0) {
						throw new flash.errors.IOError('Bad data format: MarketCPP.type2 cannot be set twice.');
					}
					++type2$count;
					this.type2 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (character2$count != 0) {
						throw new flash.errors.IOError('Bad data format: MarketCPP.character2 cannot be set twice.');
					}
					++character2$count;
					this.character2 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (type3$count != 0) {
						throw new flash.errors.IOError('Bad data format: MarketCPP.type3 cannot be set twice.');
					}
					++type3$count;
					this.type3 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (character3$count != 0) {
						throw new flash.errors.IOError('Bad data format: MarketCPP.character3 cannot be set twice.');
					}
					++character3$count;
					this.character3 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
