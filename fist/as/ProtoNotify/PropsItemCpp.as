package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class PropsItemCpp
	{
		public static const PROTO:String = "ProtoNotify.PropsItemCpp";
		public var package_root:*;
		public  var message:*;
		public var propId:int;
		public var count:int;
		public function PropsItemCpp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			propId = undefined;
			count = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.propId = this.propId;
			serializeObj.count = this.count;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PropsItemCpp
		{
			propId = undefined;
			count = undefined;
			this.propId = msgObj.propId;
			this.count = msgObj.count;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PropsItemCpp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}