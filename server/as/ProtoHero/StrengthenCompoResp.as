package ProtoHero {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.CostItemCPP;
	import ProtoComponent.ComponentCPP;
	import ProtoHero.HeroBaseInfoCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class StrengthenCompoResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const COMPO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoHero.StrengthenCompoResp.compo", "compo", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoComponent.ComponentCPP; });

		public var compo:ProtoComponent.ComponentCPP;

		/**
		 *  @private
		 */
		public static const DELCOMPOS:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoHero.StrengthenCompoResp.delcompos", "delcompos", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var delcompos:Array = [];

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoHero.StrengthenCompoResp.coin", "coin", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.CostItemCPP; });

		public var coin:DataCommon.CostItemCPP;

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoHero.StrengthenCompoResp.wood", "wood", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.CostItemCPP; });

		public var wood:DataCommon.CostItemCPP;

		/**
		 *  @private
		 */
		public static const HERO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoHero.StrengthenCompoResp.hero", "hero", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoHero.HeroBaseInfoCPP; });

		private var hero$field:ProtoHero.HeroBaseInfoCPP;

		public function clearHero():void {
			hero$field = null;
		}

		public function get hasHero():Boolean {
			return hero$field != null;
		}

		public function set hero(value:ProtoHero.HeroBaseInfoCPP):void {
			hero$field = value;
		}

		public function get hero():ProtoHero.HeroBaseInfoCPP {
			return hero$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.compo);
			for (var delcompos$index:uint = 0; delcompos$index < this.delcompos.length; ++delcompos$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.delcompos[delcompos$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.wood);
			if (hasHero) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, hero$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var compo$count:uint = 0;
			var coin$count:uint = 0;
			var wood$count:uint = 0;
			var hero$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (compo$count != 0) {
						throw new flash.errors.IOError('Bad data format: StrengthenCompoResp.compo cannot be set twice.');
					}
					++compo$count;
					this.compo = new ProtoComponent.ComponentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.compo);
					break;
				case 2:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.delcompos);
						break;
					}
					this.delcompos.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 3:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: StrengthenCompoResp.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = new DataCommon.CostItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.coin);
					break;
				case 4:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: StrengthenCompoResp.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = new DataCommon.CostItemCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.wood);
					break;
				case 5:
					if (hero$count != 0) {
						throw new flash.errors.IOError('Bad data format: StrengthenCompoResp.hero cannot be set twice.');
					}
					++hero$count;
					this.hero = new ProtoHero.HeroBaseInfoCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.hero);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
