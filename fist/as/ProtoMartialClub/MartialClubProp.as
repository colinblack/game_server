package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MartialClubProp
	{
		public static const PROTO:String = "ProtoMartialClub.MartialClubProp";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var count:int;
		public function MartialClubProp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			count = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.count = this.count;
			return serializeObj;
		}
		public function unserialize(msgObj:*):MartialClubProp
		{
			id = undefined;
			count = undefined;
			this.id = msgObj.id;
			this.count = msgObj.count;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MartialClubProp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}