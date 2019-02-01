package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoPartimeInfo
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoPartimeInfo";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public var heroInfo:MartialHeroBaseInfo;
		public function ProtoPartimeInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			grade = undefined;
			heroInfo = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.grade = this.grade;
			serializeObj.heroInfo = this.heroInfo.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoPartimeInfo
		{
			grade = undefined;
			heroInfo = undefined;
			this.grade = msgObj.grade;
			this.heroInfo = new MartialHeroBaseInfo(package_root).unserialize(msgObj.heroInfo);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoPartimeInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}