package com.sanguo.game.server.connectlogic.common.message.DataCommon
{
	import laya.utils.Byte;
	public class PropsItemCPP
	{
		public static const PROTO:String = "DataCommon.PropsItemCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var propsId:int;
		public var itemCnt:int;
		public function PropsItemCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			propsId = undefined;
			itemCnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.propsId = this.propsId;
			serializeObj.itemCnt = this.itemCnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PropsItemCPP
		{
			ud = undefined;
			propsId = undefined;
			itemCnt = undefined;
			this.ud = msgObj.ud;
			this.propsId = msgObj.propsId;
			this.itemCnt = msgObj.itemCnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PropsItemCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}