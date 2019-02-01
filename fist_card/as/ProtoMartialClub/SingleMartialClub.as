package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class SingleMartialClub
	{
		public static const PROTO:String = "ProtoMartialClub.SingleMartialClub";
		public var package_root:*;
		public  var message:*;
		public var clubInfo:MartialClubInfo;
		public var heroInfo:Vector.<MartialHeroInfo>;
		public function SingleMartialClub(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			clubInfo = undefined;
			heroInfo = new Vector.<MartialHeroInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.clubInfo = this.clubInfo.serialize();
			serializeObj.heroInfo = [];
			for(var i:int = 0;i < this.heroInfo.length;i++)
			{
				serializeObj.heroInfo.push(this.heroInfo[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SingleMartialClub
		{
			clubInfo = undefined;
			heroInfo = new Vector.<MartialHeroInfo>();
			this.clubInfo = new MartialClubInfo(package_root).unserialize(msgObj.clubInfo);
			for(var i:int = 0;i < msgObj.heroInfo.length;i++)
			{
				this.heroInfo.push(new MartialHeroInfo(package_root).unserialize(msgObj.heroInfo[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SingleMartialClub
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}