package com.sanguo.game.server.connectlogic.common.message.ProtoAssistor
{
	import laya.utils.Byte;
	public class assistInfoCPP
	{
		public static const PROTO:String = "ProtoAssistor.assistInfoCPP";
		public var package_root:*;
		public  var message:*;
		public var level:int;
		public var propsId:int;
		public var propsCnt:int;
		public function assistInfoCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			level = undefined;
			propsId = undefined;
			propsCnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.level = this.level;
			serializeObj.propsId = this.propsId;
			serializeObj.propsCnt = this.propsCnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):assistInfoCPP
		{
			level = undefined;
			propsId = undefined;
			propsCnt = undefined;
			this.level = msgObj.level;
			this.propsId = msgObj.propsId;
			this.propsCnt = msgObj.propsCnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):assistInfoCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}