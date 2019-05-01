package ProtoActivity {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoActivity.TouchGoldTombItem;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class TouchGoldInfo extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const TOMBS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoActivity.TouchGoldInfo.tombs", "tombs", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoActivity.TouchGoldTombItem; });

		[ArrayElementType("ProtoActivity.TouchGoldTombItem")]
		public var tombs:Array = [];

		/**
		 *  @private
		 */
		public static const TOTAL_TOUCH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.TouchGoldInfo.total_touch", "totalTouch", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var totalTouch:uint;

		/**
		 *  @private
		 */
		public static const TOTAL_LIMIT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.TouchGoldInfo.total_limit", "totalLimit", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var totalLimit:uint;

		/**
		 *  @private
		 */
		public static const SURPLUS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.TouchGoldInfo.surplus", "surplus", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var surplus:uint;

		/**
		 *  @private
		 */
		public static const OUT:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoActivity.TouchGoldInfo.out", "out", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var out:Array = [];

		/**
		 *  @private
		 */
		public static const COMPONENT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.TouchGoldInfo.component", "component", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var component:uint;

		/**
		 *  @private
		 */
		public static const CUR_TOMB_ID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoActivity.TouchGoldInfo.cur_tomb_id", "curTombId", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var curTombId:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var tombs$index:uint = 0; tombs$index < this.tombs.length; ++tombs$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.tombs[tombs$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.totalTouch);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.totalLimit);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.surplus);
			for (var out$index:uint = 0; out$index < this.out.length; ++out$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.out[out$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.component);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.curTombId);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var total_touch$count:uint = 0;
			var total_limit$count:uint = 0;
			var surplus$count:uint = 0;
			var component$count:uint = 0;
			var cur_tomb_id$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					this.tombs.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoActivity.TouchGoldTombItem()));
					break;
				case 2:
					if (total_touch$count != 0) {
						throw new flash.errors.IOError('Bad data format: TouchGoldInfo.totalTouch cannot be set twice.');
					}
					++total_touch$count;
					this.totalTouch = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (total_limit$count != 0) {
						throw new flash.errors.IOError('Bad data format: TouchGoldInfo.totalLimit cannot be set twice.');
					}
					++total_limit$count;
					this.totalLimit = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (surplus$count != 0) {
						throw new flash.errors.IOError('Bad data format: TouchGoldInfo.surplus cannot be set twice.');
					}
					++surplus$count;
					this.surplus = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.out);
						break;
					}
					this.out.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 6:
					if (component$count != 0) {
						throw new flash.errors.IOError('Bad data format: TouchGoldInfo.component cannot be set twice.');
					}
					++component$count;
					this.component = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (cur_tomb_id$count != 0) {
						throw new flash.errors.IOError('Bad data format: TouchGoldInfo.curTombId cannot be set twice.');
					}
					++cur_tomb_id$count;
					this.curTombId = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
