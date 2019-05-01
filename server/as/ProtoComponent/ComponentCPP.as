package ProtoComponent {
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
	public dynamic final class ComponentCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const COMPUD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ComponentCPP.compud", "compud", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var compud:uint;

		/**
		 *  @private
		 */
		public static const COMPID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ComponentCPP.compid", "compid", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var compid:uint;

		/**
		 *  @private
		 */
		public static const LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ComponentCPP.level", "level", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var level:uint;

		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ComponentCPP.exp", "exp", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exp:uint;

		/**
		 *  @private
		 */
		public static const HEROID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ComponentCPP.heroid", "heroid", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var heroid:uint;

		/**
		 *  @private
		 */
		public static const POSITION:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ComponentCPP.position", "position", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var position:uint;

		/**
		 *  @private
		 */
		public static const MASTER:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoComponent.ComponentCPP.master", "master", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var master:uint;

		/**
		 *  @private
		 */
		public static const SLAVE:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoComponent.ComponentCPP.slave", "slave", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var slave:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.compud);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.compid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.level);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.exp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.heroid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.position);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.master);
			for (var slave$index:uint = 0; slave$index < this.slave.length; ++slave$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.slave[slave$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var compud$count:uint = 0;
			var compid$count:uint = 0;
			var level$count:uint = 0;
			var exp$count:uint = 0;
			var heroid$count:uint = 0;
			var position$count:uint = 0;
			var master$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (compud$count != 0) {
						throw new flash.errors.IOError('Bad data format: ComponentCPP.compud cannot be set twice.');
					}
					++compud$count;
					this.compud = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (compid$count != 0) {
						throw new flash.errors.IOError('Bad data format: ComponentCPP.compid cannot be set twice.');
					}
					++compid$count;
					this.compid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (level$count != 0) {
						throw new flash.errors.IOError('Bad data format: ComponentCPP.level cannot be set twice.');
					}
					++level$count;
					this.level = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: ComponentCPP.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (heroid$count != 0) {
						throw new flash.errors.IOError('Bad data format: ComponentCPP.heroid cannot be set twice.');
					}
					++heroid$count;
					this.heroid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (position$count != 0) {
						throw new flash.errors.IOError('Bad data format: ComponentCPP.position cannot be set twice.');
					}
					++position$count;
					this.position = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (master$count != 0) {
						throw new flash.errors.IOError('Bad data format: ComponentCPP.master cannot be set twice.');
					}
					++master$count;
					this.master = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.slave);
						break;
					}
					this.slave.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
