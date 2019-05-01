package ProtoScience {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoScience.ScienceItemCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ScienceCapitalResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ITEM:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoScience.ScienceCapitalResp.item", "item", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoScience.ScienceItemCPP; });

		public var item:ProtoScience.ScienceItemCPP;

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoScience.ScienceCapitalResp.coin", "coin", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoScience.ScienceCapitalResp.wood", "wood", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var wood:uint;

		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoScience.ScienceCapitalResp.food", "food", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var food:uint;

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoScience.ScienceCapitalResp.iron", "iron", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var iron:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.item);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.wood);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.food);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.iron);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var item$count:uint = 0;
			var coin$count:uint = 0;
			var wood$count:uint = 0;
			var food$count:uint = 0;
			var iron$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (item$count != 0) {
						throw new flash.errors.IOError('Bad data format: ScienceCapitalResp.item cannot be set twice.');
					}
					++item$count;
					this.item = new ProtoScience.ScienceItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.item);
					break;
				case 2:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: ScienceCapitalResp.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: ScienceCapitalResp.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: ScienceCapitalResp.food cannot be set twice.');
					}
					++food$count;
					this.food = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: ScienceCapitalResp.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
